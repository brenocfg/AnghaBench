#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int u_int ;
struct pcap_ng_sf {int ifcount; int ifaces_size; int user_tsresol; struct pcap_ng_if* ifaces; } ;
struct pcap_ng_if {int tsresol; int scale_factor; int /*<<< orphan*/  scale_type; scalar_t__ tsoffset; } ;
struct block_cursor {int dummy; } ;
struct TYPE_4__ {struct pcap_ng_sf* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int bpf_u_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  PASS_THROUGH ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  SCALE_DOWN_BIN ; 
 int /*<<< orphan*/  SCALE_DOWN_DEC ; 
 int /*<<< orphan*/  SCALE_UP_BIN ; 
 int /*<<< orphan*/  SCALE_UP_DEC ; 
 struct pcap_ng_if* malloc (int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int process_idb_options (TYPE_1__*,struct block_cursor*,int*,scalar_t__*,int*,char*) ; 
 struct pcap_ng_if* realloc (struct pcap_ng_if*,int) ; 

__attribute__((used)) static int
add_interface(pcap_t *p, struct block_cursor *cursor, char *errbuf)
{
	struct pcap_ng_sf *ps;
	u_int tsresol;
	uint64_t tsoffset;
	int is_binary;

	ps = p->priv;

	/*
	 * Count this interface.
	 */
	ps->ifcount++;

	/*
	 * Grow the array of per-interface information as necessary.
	 */
	if (ps->ifcount > ps->ifaces_size) {
		/*
		 * We need to grow the array.
		 */
		bpf_u_int32 new_ifaces_size;
		struct pcap_ng_if *new_ifaces;

		if (ps->ifaces_size == 0) {
			/*
			 * It's currently empty.
			 *
			 * (The Clang static analyzer doesn't do enough,
			 * err, umm, dataflow *analysis* to realize that
			 * ps->ifaces_size == 0 if ps->ifaces == NULL,
			 * and so complains about a possible zero argument
			 * to realloc(), so we check for the former
			 * condition to shut it up.
			 *
			 * However, it doesn't complain that one of the
			 * multiplications below could overflow, which is
			 * a real, albeit extremely unlikely, problem (you'd
			 * need a pcapng file with tens of millions of
			 * interfaces).)
			 */
			new_ifaces_size = 1;
			new_ifaces = malloc(sizeof (struct pcap_ng_if));
		} else {
			/*
			 * It's not currently empty; double its size.
			 * (Perhaps overkill once we have a lot of interfaces.)
			 *
			 * Check for overflow if we double it.
			 */
			if (ps->ifaces_size * 2 < ps->ifaces_size) {
				/*
				 * The maximum number of interfaces before
				 * ps->ifaces_size overflows is the largest
				 * possible 32-bit power of 2, as we do
				 * size doubling.
				 */
				pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "more than %u interfaces in the file",
				    0x80000000U);
				return (0);
			}

			/*
			 * ps->ifaces_size * 2 doesn't overflow, so it's
			 * safe to multiply.
			 */
			new_ifaces_size = ps->ifaces_size * 2;

			/*
			 * Now make sure that's not so big that it overflows
			 * if we multiply by sizeof (struct pcap_ng_if).
			 *
			 * That can happen on 32-bit platforms, with a 32-bit
			 * size_t; it shouldn't happen on 64-bit platforms,
			 * with a 64-bit size_t, as new_ifaces_size is
			 * 32 bits.
			 */
			if (new_ifaces_size * sizeof (struct pcap_ng_if) < new_ifaces_size) {
				/*
				 * As this fails only with 32-bit size_t,
				 * the multiplication was 32x32->32, and
				 * the largest 32-bit value that can safely
				 * be multiplied by sizeof (struct pcap_ng_if)
				 * without overflow is the largest 32-bit
				 * (unsigned) value divided by
				 * sizeof (struct pcap_ng_if).
				 */
				pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "more than %u interfaces in the file",
				    0xFFFFFFFFU / ((u_int)sizeof (struct pcap_ng_if)));
				return (0);
			}
			new_ifaces = realloc(ps->ifaces, new_ifaces_size * sizeof (struct pcap_ng_if));
		}
		if (new_ifaces == NULL) {
			/*
			 * We ran out of memory.
			 * Give up.
			 */
			pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
			    "out of memory for per-interface information (%u interfaces)",
			    ps->ifcount);
			return (0);
		}
		ps->ifaces_size = new_ifaces_size;
		ps->ifaces = new_ifaces;
	}

	/*
	 * Set the default time stamp resolution and offset.
	 */
	tsresol = 1000000;	/* microsecond resolution */
	is_binary = 0;		/* which is a power of 10 */
	tsoffset = 0;		/* absolute timestamps */

	/*
	 * Now look for various time stamp options, so we know
	 * how to interpret the time stamps for this interface.
	 */
	if (process_idb_options(p, cursor, &tsresol, &tsoffset, &is_binary,
	    errbuf) == -1)
		return (0);

	ps->ifaces[ps->ifcount - 1].tsresol = tsresol;
	ps->ifaces[ps->ifcount - 1].tsoffset = tsoffset;

	/*
	 * Determine whether we're scaling up or down or not
	 * at all for this interface.
	 */
	if (tsresol == ps->user_tsresol) {
		/*
		 * The resolution is the resolution the user wants,
		 * so we don't have to do scaling.
		 */
		ps->ifaces[ps->ifcount - 1].scale_type = PASS_THROUGH;
	} else if (tsresol > ps->user_tsresol) {
		/*
		 * The resolution is greater than what the user wants,
		 * so we have to scale the timestamps down.
		 */
		if (is_binary)
			ps->ifaces[ps->ifcount - 1].scale_type = SCALE_DOWN_BIN;
		else {
			/*
			 * Calculate the scale factor.
			 */
			ps->ifaces[ps->ifcount - 1].scale_factor = tsresol/ps->user_tsresol;
			ps->ifaces[ps->ifcount - 1].scale_type = SCALE_DOWN_DEC;
		}
	} else {
		/*
		 * The resolution is less than what the user wants,
		 * so we have to scale the timestamps up.
		 */
		if (is_binary)
			ps->ifaces[ps->ifcount - 1].scale_type = SCALE_UP_BIN;
		else {
			/*
			 * Calculate the scale factor.
			 */
			ps->ifaces[ps->ifcount - 1].scale_factor = ps->user_tsresol/tsresol;
			ps->ifaces[ps->ifcount - 1].scale_type = SCALE_UP_DEC;
		}
	}
	return (1);
}
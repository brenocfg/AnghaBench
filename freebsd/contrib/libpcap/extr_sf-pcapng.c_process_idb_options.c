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
typedef  int uint64_t ;
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  tsresol_opt ;
struct option_header {int option_code; int option_length; } ;
struct block_cursor {scalar_t__ data_remaining; } ;
struct TYPE_4__ {int /*<<< orphan*/  swapped; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
#define  IF_TSOFFSET 130 
#define  IF_TSRESOL 129 
#define  OPT_ENDOFOPT 128 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int SWAPLL (int) ; 
 struct option_header* get_opthdr_from_block_data (TYPE_1__*,struct block_cursor*,char*) ; 
 void* get_optvalue_from_block_data (struct block_cursor*,struct option_header*,char*) ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
process_idb_options(pcap_t *p, struct block_cursor *cursor, u_int *tsresol,
    uint64_t *tsoffset, int *is_binary, char *errbuf)
{
	struct option_header *opthdr;
	void *optvalue;
	int saw_tsresol, saw_tsoffset;
	u_char tsresol_opt;
	u_int i;

	saw_tsresol = 0;
	saw_tsoffset = 0;
	while (cursor->data_remaining != 0) {
		/*
		 * Get the option header.
		 */
		opthdr = get_opthdr_from_block_data(p, cursor, errbuf);
		if (opthdr == NULL) {
			/*
			 * Option header is cut short.
			 */
			return (-1);
		}

		/*
		 * Get option value.
		 */
		optvalue = get_optvalue_from_block_data(cursor, opthdr,
		    errbuf);
		if (optvalue == NULL) {
			/*
			 * Option value is cut short.
			 */
			return (-1);
		}

		switch (opthdr->option_code) {

		case OPT_ENDOFOPT:
			if (opthdr->option_length != 0) {
				pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "Interface Description Block has opt_endofopt option with length %u != 0",
				    opthdr->option_length);
				return (-1);
			}
			goto done;

		case IF_TSRESOL:
			if (opthdr->option_length != 1) {
				pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "Interface Description Block has if_tsresol option with length %u != 1",
				    opthdr->option_length);
				return (-1);
			}
			if (saw_tsresol) {
				pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "Interface Description Block has more than one if_tsresol option");
				return (-1);
			}
			saw_tsresol = 1;
			memcpy(&tsresol_opt, optvalue, sizeof(tsresol_opt));
			if (tsresol_opt & 0x80) {
				/*
				 * Resolution is negative power of 2.
				 */
				*is_binary = 1;
				*tsresol = 1 << (tsresol_opt & 0x7F);
			} else {
				/*
				 * Resolution is negative power of 10.
				 */
				*is_binary = 0;
				*tsresol = 1;
				for (i = 0; i < tsresol_opt; i++)
					*tsresol *= 10;
			}
			if (*tsresol == 0) {
				/*
				 * Resolution is too high.
				 */
				if (tsresol_opt & 0x80) {
					pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
					    "Interface Description Block if_tsresol option resolution 2^-%u is too high",
					    tsresol_opt & 0x7F);
				} else {
					pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
					    "Interface Description Block if_tsresol option resolution 10^-%u is too high",
					    tsresol_opt);
				}
				return (-1);
			}
			break;

		case IF_TSOFFSET:
			if (opthdr->option_length != 8) {
				pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "Interface Description Block has if_tsoffset option with length %u != 8",
				    opthdr->option_length);
				return (-1);
			}
			if (saw_tsoffset) {
				pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "Interface Description Block has more than one if_tsoffset option");
				return (-1);
			}
			saw_tsoffset = 1;
			memcpy(tsoffset, optvalue, sizeof(*tsoffset));
			if (p->swapped)
				*tsoffset = SWAPLL(*tsoffset);
			break;

		default:
			break;
		}
	}

done:
	return (0);
}
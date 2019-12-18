#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
union bhnd_nvram_btxt_ident {char* btxt; int /*<<< orphan*/  bcm_magic; } ;
struct bhnd_nvram_io {int dummy; } ;
typedef  int /*<<< orphan*/  ident ;

/* Variables and functions */
 scalar_t__ BCM_NVRAM_MAGIC ; 
 int BHND_NVRAM_DATA_PROBE_MAYBE ; 
 int ENXIO ; 
 int /*<<< orphan*/  bhnd_nv_isalpha (char) ; 
 int /*<<< orphan*/  bhnd_nv_isprint (char) ; 
 int /*<<< orphan*/  bhnd_nv_isspace (char) ; 
 int bhnd_nvram_io_read (struct bhnd_nvram_io*,int,union bhnd_nvram_btxt_ident*,int) ; 
 scalar_t__ le32toh (int /*<<< orphan*/ ) ; 
 size_t nitems (char*) ; 

__attribute__((used)) static int
bhnd_nvram_btxt_probe(struct bhnd_nvram_io *io)
{
	union bhnd_nvram_btxt_ident	ident;
	char				c;
	int				error;

	/* Look at the initial header for something that looks like 
	 * an ASCII board text file */
	if ((error = bhnd_nvram_io_read(io, 0x0, &ident, sizeof(ident))))
		return (error);

	/* The BCM NVRAM format uses a 'FLSH' little endian magic value, which
	 * shouldn't be interpreted as BTXT */
	if (le32toh(ident.bcm_magic) == BCM_NVRAM_MAGIC)
		return (ENXIO);

	/* Don't match on non-ASCII/non-printable data */
	for (size_t i = 0; i < nitems(ident.btxt); i++) {
		c = ident.btxt[i];
		if (!bhnd_nv_isprint(c))
			return (ENXIO);
	}

	/* The first character should either be a valid key char (alpha),
	 * whitespace, or the start of a comment ('#') */
	c = ident.btxt[0];
	if (!bhnd_nv_isspace(c) && !bhnd_nv_isalpha(c) && c != '#')
		return (ENXIO);

	/* We assert a low priority, given that we've only scanned an
	 * initial few bytes of the file. */
	return (BHND_NVRAM_DATA_PROBE_MAYBE);
}
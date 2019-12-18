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
typedef  scalar_t__ uint8_t ;
struct spi_options {int ncmd; scalar_t__ lsb; scalar_t__* pcmd; } ;

/* Variables and functions */
 int DEFAULT_BUFFER_SIZE ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int hexval (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 void* realloc (scalar_t__*,int) ; 
 scalar_t__* reversebits ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
interpret_command_bytes(const char *parg, struct spi_options *popt)
{
	int ch, ch2, ctr, cbcmd, err;
	const char *ppos;
	void *ptemp;
	uint8_t *pcur;

	err = 0;
	cbcmd = DEFAULT_BUFFER_SIZE; /* initial cmd buffer size */
	popt->pcmd = (uint8_t *)malloc(cbcmd);

	if (!popt->pcmd)
		return 1;

	pcur = popt->pcmd;

	ctr = 0;
	ppos = parg;

	while (*ppos) {
		while (*ppos && *ppos <= ' ') {
			ppos++; /* skip (optional) leading white space */
		}

		if (!*ppos)
			break; /* I am done */

		ch = hexval(*(ppos++));
		if (ch < 0 || !*ppos) { /* must be valid pair of hex characters */
			err = 1;
			goto the_end;
		}
		
		ch2 = hexval(*(ppos++));
		if (ch2 < 0) {
			err = 1;
			goto the_end;
		}

		ch = (ch * 16 + ch2) & 0xff; /* convert to byte */

		if (ctr >= cbcmd) { /* need re-alloc buffer? (unlikely) */
			cbcmd += 8192; /* increase by additional 8k */
			ptemp = realloc(popt->pcmd, cbcmd);

			if (!ptemp) {
				err = 1;
				fprintf(stderr,
					"Not enough memory to interpret command bytes, errno=%d\n",
					errno);
				goto the_end;
			}

			popt->pcmd = (uint8_t *)ptemp;
			pcur = popt->pcmd + ctr;
		}

		if (popt->lsb)
			*pcur = reversebits[ch];
		else
			*pcur = (uint8_t)ch;

		pcur++;
		ctr++;
	}

	popt->ncmd = ctr; /* record num bytes in '-C' argument */

the_end:

	/* at this point popt->pcmd is NULL or a valid pointer */

	return err;
}
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
typedef  scalar_t__ uint32_t ;
typedef  int u_char ;
typedef  scalar_t__ lba_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOSMAGIC ; 
 int DOSMAGICOFFSET ; 
 int DOSPARTOFF ; 
 scalar_t__ UINT32_MAX ; 
 int errno ; 
 int /*<<< orphan*/  free (int*) ; 
 int image_write (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  le16enc (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32enc (int*,scalar_t__) ; 
 int* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ secsz ; 

__attribute__((used)) static int
gpt_write_pmbr(lba_t blks, void *bootcode)
{
	u_char *pmbr;
	uint32_t secs;
	int error;

	secs = (blks > UINT32_MAX) ? UINT32_MAX : (uint32_t)blks - 1;

	pmbr = malloc(secsz);
	if (pmbr == NULL)
		return (errno);
	if (bootcode != NULL) {
		memcpy(pmbr, bootcode, DOSPARTOFF);
		memset(pmbr + DOSPARTOFF, 0, secsz - DOSPARTOFF);
	} else
		memset(pmbr, 0, secsz);
	pmbr[DOSPARTOFF + 2] = 2;
	pmbr[DOSPARTOFF + 4] = 0xee;
	pmbr[DOSPARTOFF + 5] = 0xff;
	pmbr[DOSPARTOFF + 6] = 0xff;
	pmbr[DOSPARTOFF + 7] = 0xff;
	le32enc(pmbr + DOSPARTOFF + 8, 1);
	le32enc(pmbr + DOSPARTOFF + 12, secs);
	le16enc(pmbr + DOSMAGICOFFSET, DOSMAGIC);
	error = image_write(0, pmbr, 1);
	free(pmbr);
	return (error);
}
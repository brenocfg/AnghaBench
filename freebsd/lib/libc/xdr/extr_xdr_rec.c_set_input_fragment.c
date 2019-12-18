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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_4__ {int fbtbc; int /*<<< orphan*/  last_frag; scalar_t__ nonblock; } ;
typedef  TYPE_1__ RECSTREAM ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LAST_FRAG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_input_bytes (TYPE_1__*,char*,int) ; 
 int ntohl (int) ; 

__attribute__((used)) static bool_t  /* next two bytes of the input stream are treated as a header */
set_input_fragment(RECSTREAM *rstrm)
{
	u_int32_t header;

	if (rstrm->nonblock)
		return FALSE;
	if (! get_input_bytes(rstrm, (char *)(void *)&header, sizeof(header)))
		return (FALSE);
	header = ntohl(header);
	rstrm->last_frag = ((header & LAST_FRAG) == 0) ? FALSE : TRUE;
	/*
	 * Sanity check. Try not to accept wildly incorrect
	 * record sizes. Unfortunately, the only record size
	 * we can positively identify as being 'wildly incorrect'
	 * is zero. Ridiculously large record sizes may look wrong,
	 * but we don't have any way to be certain that they aren't
	 * what the client actually intended to send us.
	 */
	if (header == 0)
		return(FALSE);
	rstrm->fbtbc = header & (~LAST_FRAG);
	return (TRUE);
}
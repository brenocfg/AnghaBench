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
typedef  int /*<<< orphan*/  KEYCMD ;

/* Variables and functions */
#define  CcEmacsMap 130 
#define  CcViCmdMap 129 
#define  CcViMap 128 
 int MapsAreInited ; 
 int NT_NUM_KEYS ; 
 size_t* _toebcdic ; 
 int /*<<< orphan*/  ed_InitEmacsMaps () ; 
 int /*<<< orphan*/  ed_InitVIMaps () ; 

void
ed_InitMaps(void)
{
    if (MapsAreInited)
	return;
#ifndef IS_ASCII
    /* This machine has an EBCDIC charset. The assumptions made for the
     * initialized keymaps therefore don't hold, since they are based on
     * ASCII (or ISO8859-1).
     * Here, we do a one-time transformation to EBCDIC environment
     * for the key initializations.
     */
    {
	KEYCMD temp[NT_NUM_KEYS];
	static KEYCMD *const list[3] = { CcEmacsMap, CcViMap, CcViCmdMap };
	int i, table;

	for (table=0; table<3; ++table)
	{
	    /* copy ASCII ordered map to temp table */
	    for (i = 0; i < NT_NUM_KEYS; i++) {
		temp[i] = list[table][i];
	    }
	    /* write back as EBCDIC ordered map */
	    for (i = 0; i < NT_NUM_KEYS; i++) {
		list[table][_toebcdic[i]] = temp[i];
	    }
	}
    }
#endif /* !IS_ASCII */

#ifdef VIDEFAULT
    ed_InitVIMaps();
#else
    ed_InitEmacsMaps();
#endif

    MapsAreInited = 1;
}
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
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  DT_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  CmCleanupAndExit () ; 
 int /*<<< orphan*/  DtError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  exit (int) ; 

void
DtFatal (
    UINT16                  MessageId,
    DT_FIELD                *FieldObject,
    char                    *ExtraMessage)
{

    DtError (ASL_ERROR, MessageId, FieldObject, ExtraMessage);

/*
 * TBD: remove this entire function, DtFatal
 *
 * We cannot abort the compiler on error, because we may be compiling a
 * list of files. We must move on to the next file.
 */
#ifdef __OBSOLETE
    CmCleanupAndExit ();
    exit (1);
#endif
}
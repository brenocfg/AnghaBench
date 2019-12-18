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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  MessageId; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_1__ ASL_ERROR_MSG ;

/* Variables and functions */
 char* AeDecodeMessageId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AePrintErrorSourceLine (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
AePrintSubError (
    FILE                    *OutputFile,
    ASL_ERROR_MSG           *Enode)
{
    UINT32                  Total = 0;
    BOOLEAN                 PrematureEOF = FALSE;
    const char              *MainMessage;


    MainMessage = AeDecodeMessageId (Enode->MessageId);

    fprintf (OutputFile, "    %s%s", MainMessage, "\n    ");
    (void) AePrintErrorSourceLine (OutputFile, Enode, &PrematureEOF, &Total);
    fprintf (OutputFile, "\n");
}
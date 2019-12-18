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

/* Variables and functions */
 int /*<<< orphan*/  ASL_PARSE_TREE_HEADER2 ; 
 int /*<<< orphan*/  ASL_TREE_OUTPUT ; 
 int ASL_WALK_VISIT_DB_SEPARATELY ; 
 int ASL_WALK_VISIT_DOWNWARD ; 
 int /*<<< orphan*/  AslGbl_CurrentDB ; 
 int /*<<< orphan*/  CgAmlWriteWalk ; 
 int /*<<< orphan*/  CgUpdateHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TrWalkParseTree (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
CgGenerateAmlOutput (
    void)
{

    /* Generate the AML output file */

    TrWalkParseTree (AslGbl_CurrentDB,
        ASL_WALK_VISIT_DOWNWARD | ASL_WALK_VISIT_DB_SEPARATELY,
        CgAmlWriteWalk, NULL, NULL);

    DbgPrint (ASL_TREE_OUTPUT, ASL_PARSE_TREE_HEADER2);
    CgUpdateHeader (AslGbl_CurrentDB);
}
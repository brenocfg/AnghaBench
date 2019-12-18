#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  Filename; } ;
typedef  int /*<<< orphan*/  ASL_GLOBAL_FILE_NODE ;

/* Variables and functions */
 size_t ASL_FILE_INPUT ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/ * FlGetFileNode (size_t,int /*<<< orphan*/ ) ; 

ASL_GLOBAL_FILE_NODE *
FlGetCurrentFileNode (
    void)
{
    return (FlGetFileNode (
        ASL_FILE_INPUT,AslGbl_Files[ASL_FILE_INPUT].Filename));
}
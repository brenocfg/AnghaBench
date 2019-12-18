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
struct TYPE_2__ {scalar_t__ isTabFunc; } ;
struct SrcList_item {int /*<<< orphan*/  zName; TYPE_1__ fg; } ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cannotBeFunction(Parse *pParse, struct SrcList_item *pFrom){
  if( pFrom->fg.isTabFunc ){
    sqlite3ErrorMsg(pParse, "'%s' is not a function", pFrom->zName);
    return 1;
  }
  return 0;
}
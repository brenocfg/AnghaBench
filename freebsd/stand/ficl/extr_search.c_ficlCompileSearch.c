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
struct TYPE_4__ {int /*<<< orphan*/ * dp; } ;
typedef  TYPE_1__ FICL_SYSTEM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  FICL_DEFAULT_VOCS ; 
 int /*<<< orphan*/  FICL_TRUE ; 
 int /*<<< orphan*/  FW_DEFAULT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  definitions ; 
 int /*<<< orphan*/  dictAppendWord (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ficlSetEnv (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ficlWordlist ; 
 int /*<<< orphan*/  forthWordlist ; 
 int /*<<< orphan*/  getCurrent ; 
 int /*<<< orphan*/  getOrder ; 
 int /*<<< orphan*/  searchPop ; 
 int /*<<< orphan*/  searchPush ; 
 int /*<<< orphan*/  searchWordlist ; 
 int /*<<< orphan*/  setCurrent ; 
 int /*<<< orphan*/  setOrder ; 
 int /*<<< orphan*/  setParentWid ; 
 int /*<<< orphan*/  widGetName ; 
 int /*<<< orphan*/  widSetName ; 

void ficlCompileSearch(FICL_SYSTEM *pSys)
{
    FICL_DICT *dp = pSys->dp;
    assert (dp);

    /*
    ** optional SEARCH-ORDER word set 
    */
    dictAppendWord(dp, ">search",   searchPush,     FW_DEFAULT);
    dictAppendWord(dp, "search>",   searchPop,      FW_DEFAULT);
    dictAppendWord(dp, "definitions",
                                    definitions,    FW_DEFAULT);
    dictAppendWord(dp, "forth-wordlist",  
                                    forthWordlist,  FW_DEFAULT);
    dictAppendWord(dp, "get-current",  
                                    getCurrent,     FW_DEFAULT);
    dictAppendWord(dp, "get-order", getOrder,       FW_DEFAULT);
    dictAppendWord(dp, "search-wordlist",  
                                    searchWordlist, FW_DEFAULT);
    dictAppendWord(dp, "set-current",  
                                    setCurrent,     FW_DEFAULT);
    dictAppendWord(dp, "set-order", setOrder,       FW_DEFAULT);
    dictAppendWord(dp, "ficl-wordlist", 
                                    ficlWordlist,   FW_DEFAULT);

    /*
    ** Set SEARCH environment query values
    */
    ficlSetEnv(pSys, "search-order",      FICL_TRUE);
    ficlSetEnv(pSys, "search-order-ext",  FICL_TRUE);
    ficlSetEnv(pSys, "wordlists",         FICL_DEFAULT_VOCS);

    dictAppendWord(dp, "wid-get-name", widGetName,  FW_DEFAULT);
    dictAppendWord(dp, "wid-set-name", widSetName,  FW_DEFAULT);
    dictAppendWord(dp, "wid-set-super", 
                                    setParentWid,   FW_DEFAULT);
    return;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ tdData; } ;
typedef  TYPE_1__ tiRoot_t ;
struct TYPE_7__ {int /*<<< orphan*/  tdsaAllShared; } ;
typedef  TYPE_2__ tdsaRoot_t ;
struct TYPE_8__ {int CardID; int /*<<< orphan*/  CardIDString; } ;
typedef  TYPE_3__ tdsaContext_t ;
typedef  int bit32 ;

/* Variables and functions */
 int /*<<< orphan*/  TI_DBG1 (char*) ; 
 int /*<<< orphan*/  TI_DBG3 (char*) ; 
 int /*<<< orphan*/  osti_sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  osti_strcpy (int /*<<< orphan*/ ,char*) ; 
 int tdsaGetCardID (TYPE_1__*) ; 
 int tiError ; 
 int tiSuccess ; 

bit32 tdsaGetCardIDString(tiRoot_t *tiRoot)
{
  tdsaRoot_t     *tdsaRoot = (tdsaRoot_t *) tiRoot->tdData;
  tdsaContext_t  *tdsaAllShared = (tdsaContext_t *)&(tdsaRoot->tdsaAllShared);
  bit32          ret = tiError;
  bit32          thisCardID = tdsaGetCardID(tiRoot);
  char           CardNum[10];
    
  TI_DBG3(("tdsaGetCardIDString: start\n"));

  TI_DBG3(("tdsaGetCardIDString: thisCardID 0x%x\n", thisCardID));
  

  if (thisCardID == 0xFFFFFFFF)
  {
    TI_DBG1(("tdGetCardIDString: No more CardIDs available\n"));
    ret = tiError;
  }
  else
  {
    tdsaAllShared->CardID = thisCardID;
    osti_sprintf(CardNum,"CardNum%d", thisCardID);
    TI_DBG3(("tdsaGetCardIDString: CardNum is %s\n", CardNum));  
    osti_strcpy(tdsaAllShared->CardIDString, CardNum);
    TI_DBG3(("tdsaGetCardIDString: tdsaAllShared->CardIDString is %s\n", tdsaAllShared->CardIDString));    
    ret = tiSuccess;
  
  }  
  return ret;
}
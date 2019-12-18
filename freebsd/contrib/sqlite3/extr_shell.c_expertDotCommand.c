#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bVerbose; int /*<<< orphan*/  pExpert; } ;
struct TYPE_4__ {TYPE_2__ expert; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ ShellState ;
typedef  int /*<<< orphan*/  ExpertInfo ;

/* Variables and functions */
 int /*<<< orphan*/  EXPERT_CONFIG_SAMPLE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ integerValue (char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sqlite3_expert_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_expert_new (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen30 (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int expertDotCommand(
  ShellState *pState,             /* Current shell tool state */
  char **azArg,                   /* Array of arguments passed to dot command */
  int nArg                        /* Number of entries in azArg[] */
){
  int rc = SQLITE_OK;
  char *zErr = 0;
  int i;
  int iSample = 0;

  assert( pState->expert.pExpert==0 );
  memset(&pState->expert, 0, sizeof(ExpertInfo));

  for(i=1; rc==SQLITE_OK && i<nArg; i++){
    char *z = azArg[i];
    int n;
    if( z[0]=='-' && z[1]=='-' ) z++;
    n = strlen30(z);
    if( n>=2 && 0==strncmp(z, "-verbose", n) ){
      pState->expert.bVerbose = 1;
    }
    else if( n>=2 && 0==strncmp(z, "-sample", n) ){
      if( i==(nArg-1) ){
        raw_printf(stderr, "option requires an argument: %s\n", z);
        rc = SQLITE_ERROR;
      }else{
        iSample = (int)integerValue(azArg[++i]);
        if( iSample<0 || iSample>100 ){
          raw_printf(stderr, "value out of range: %s\n", azArg[i]);
          rc = SQLITE_ERROR;
        }
      }
    }
    else{
      raw_printf(stderr, "unknown option: %s\n", z);
      rc = SQLITE_ERROR;
    }
  }

  if( rc==SQLITE_OK ){
    pState->expert.pExpert = sqlite3_expert_new(pState->db, &zErr);
    if( pState->expert.pExpert==0 ){
      raw_printf(stderr, "sqlite3_expert_new: %s\n", zErr);
      rc = SQLITE_ERROR;
    }else{
      sqlite3_expert_config(
          pState->expert.pExpert, EXPERT_CONFIG_SAMPLE, iSample
      );
    }
  }

  return rc;
}
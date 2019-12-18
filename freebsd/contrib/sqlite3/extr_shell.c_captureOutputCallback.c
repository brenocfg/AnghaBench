#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ n; } ;
typedef  TYPE_1__ ShellText ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (char**) ; 
 int /*<<< orphan*/  appendText (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int captureOutputCallback(void *pArg, int nArg, char **azArg, char **az){
  ShellText *p = (ShellText*)pArg;
  int i;
  UNUSED_PARAMETER(az);
  if( azArg==0 ) return 0;
  if( p->n ) appendText(p, "|", 0);
  for(i=0; i<nArg; i++){
    if( i ) appendText(p, ",", 0);
    if( azArg[i] ) appendText(p, azArg[i], 0);
  }
  return 0;
}
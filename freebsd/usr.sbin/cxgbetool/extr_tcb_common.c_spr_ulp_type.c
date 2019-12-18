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
 unsigned int PM_MODE_DDP ; 
 unsigned int PM_MODE_DTLS ; 
 unsigned int PM_MODE_FCOE ; 
 unsigned int PM_MODE_IANDP ; 
 unsigned int PM_MODE_ISCSI ; 
 unsigned int PM_MODE_IWARP ; 
 unsigned int PM_MODE_PASS ; 
 unsigned int PM_MODE_RDDP ; 
 unsigned int PM_MODE_TLS ; 
 unsigned int PM_MODE_USER ; 

char *
spr_ulp_type(unsigned ulp_type)
{
  char *ret="UNKNOWN";

  /*The tp.h PM_MODE_XXX call 1 DDP and 5 IANDP, but external
   * documentation (tcb.h" calls 5 ddp, and doesn't mention 1 or 3.
   */
  
  if      ( PM_MODE_PASS  == ulp_type) {ret = "TOE";}
  else if ( PM_MODE_DDP   == ulp_type) {ret = "DDP";}
  else if ( PM_MODE_ISCSI == ulp_type) {ret = "ISCSI";}
  else if ( PM_MODE_IWARP == ulp_type) {ret = "IWARP";}
  else if ( PM_MODE_RDDP  == ulp_type) {ret = "RDMA";}
  else if ( PM_MODE_IANDP == ulp_type) {ret = "IANDP_DDP";}
  else if ( PM_MODE_FCOE  == ulp_type) {ret = "FCoE";}
  else if ( PM_MODE_USER  == ulp_type) {ret = "USER";}
  else if ( PM_MODE_TLS   == ulp_type) {ret = "TLS";}
  else if ( PM_MODE_DTLS  == ulp_type) {ret = "DTLS";}

  return ret;
}
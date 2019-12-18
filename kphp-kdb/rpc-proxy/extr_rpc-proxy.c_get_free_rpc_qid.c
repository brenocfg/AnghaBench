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
 long long last_qid ; 
 long long lrand48 () ; 

long long get_free_rpc_qid (long long qid) {
  last_qid += lrand48 () ;
  last_qid ++;
  return last_qid;
}
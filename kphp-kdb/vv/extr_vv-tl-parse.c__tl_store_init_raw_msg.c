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
struct udp_target {int /*<<< orphan*/  PID; } ;
struct raw_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TL_OUT_PID ; 
 int __tl_store_init (struct raw_message*,struct udp_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,long long) ; 
 int /*<<< orphan*/  rwm_init (struct raw_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_out_raw_msg_methods ; 
 int /*<<< orphan*/  tl_type_raw_msg ; 
 scalar_t__ zmalloc (int) ; 

__attribute__((used)) static inline int _tl_store_init_raw_msg (struct udp_target *S, long long qid, int keep_error) {
  if (S) {
    TL_OUT_PID = &(S->PID);
  } else {
    TL_OUT_PID = 0;
  }
  struct raw_message *d = 0;
  if (S) {
    d = (struct raw_message *)zmalloc (sizeof (*d));
    rwm_init (d, 0);
  }
  return __tl_store_init (d, S, tl_type_raw_msg, &tl_out_raw_msg_methods, (1 << 27), keep_error, qid);
}
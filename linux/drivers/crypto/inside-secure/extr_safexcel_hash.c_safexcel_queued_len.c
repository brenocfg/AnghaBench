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
typedef  scalar_t__ u64 ;
struct safexcel_ahash_req {scalar_t__ processed; scalar_t__ len; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 safexcel_queued_len(struct safexcel_ahash_req *req)
{
	return req->len - req->processed;
}
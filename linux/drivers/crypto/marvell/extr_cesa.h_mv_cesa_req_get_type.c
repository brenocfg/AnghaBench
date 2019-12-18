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
struct TYPE_2__ {scalar_t__ first; } ;
struct mv_cesa_req {TYPE_1__ chain; } ;
typedef  enum mv_cesa_req_type { ____Placeholder_mv_cesa_req_type } mv_cesa_req_type ;

/* Variables and functions */
 int CESA_DMA_REQ ; 
 int CESA_STD_REQ ; 

__attribute__((used)) static inline enum mv_cesa_req_type
mv_cesa_req_get_type(struct mv_cesa_req *req)
{
	return req->chain.first ? CESA_DMA_REQ : CESA_STD_REQ;
}
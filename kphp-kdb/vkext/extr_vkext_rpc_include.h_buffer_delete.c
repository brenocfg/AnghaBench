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
struct rpc_buffer {scalar_t__ sptr; scalar_t__ eptr; scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  zzefree (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  zzfree (struct rpc_buffer*,int) ; 

__attribute__((used)) static struct rpc_buffer *buffer_delete (struct rpc_buffer *buf) {
  buf->magic = 0;
  zzefree (buf->sptr, buf->eptr - buf->sptr);
  zzfree (buf, sizeof (*buf));
  return 0;
}
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
struct sm_sendq {int dummy; } ;
typedef  TYPE_1__* sm_sendq_t ;
struct TYPE_4__ {int recv_fd; char* begin; char* head; char* tail; void* value; } ;

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

sm_sendq_t sm_sendq_new(int recv_fd, void *value, const char *data,
    size_t length) {
  sm_sendq_t ret = (sm_sendq_t)malloc(sizeof(struct sm_sendq));
  memset(ret, 0, sizeof(struct sm_sendq));
  ret->recv_fd = recv_fd;
  ret->value = value;
  ret->begin = (char *)malloc(length);
  memcpy(ret->begin, data, length);
  ret->head = ret->begin;
  ret->tail = ret->begin + length;
  return ret;
}
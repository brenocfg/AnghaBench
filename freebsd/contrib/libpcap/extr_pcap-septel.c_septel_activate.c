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
struct TYPE_4__ {scalar_t__ snapshot; int selectable_fd; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/ * set_datalink_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  inject_op; int /*<<< orphan*/  read_op; scalar_t__ bufsize; int /*<<< orphan*/  linktype; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_MTP2 ; 
 scalar_t__ MAXIMUM_SNAPLEN ; 
 int /*<<< orphan*/  septel_getnonblock ; 
 int /*<<< orphan*/  septel_inject ; 
 int /*<<< orphan*/  septel_read ; 
 int /*<<< orphan*/  septel_setfilter ; 
 int /*<<< orphan*/  septel_setnonblock ; 
 int /*<<< orphan*/  septel_stats ; 

__attribute__((used)) static pcap_t *septel_activate(pcap_t* handle) {
  /* Initialize some components of the pcap structure. */
  handle->linktype = DLT_MTP2;

  /*
   * Turn a negative snapshot value (invalid), a snapshot value of
   * 0 (unspecified), or a value bigger than the normal maximum
   * value, into the maximum allowed value.
   *
   * If some application really *needs* a bigger snapshot
   * length, we should just increase MAXIMUM_SNAPLEN.
   */
  if (handle->snapshot <= 0 || handle->snapshot > MAXIMUM_SNAPLEN)
    handle->snapshot = MAXIMUM_SNAPLEN;

  handle->bufsize = 0;

  /*
   * "select()" and "poll()" don't work on Septel queues
   */
  handle->selectable_fd = -1;

  handle->read_op = septel_read;
  handle->inject_op = septel_inject;
  handle->setfilter_op = septel_setfilter;
  handle->set_datalink_op = NULL; /* can't change data link type */
  handle->getnonblock_op = septel_getnonblock;
  handle->setnonblock_op = septel_setnonblock;
  handle->stats_op = septel_stats;

  return 0;
}
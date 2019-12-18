#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_8__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_10__ {scalar_t__ st_size; scalar_t__ st_mode; scalar_t__ st_uid; scalar_t__ st_gid; scalar_t__ st_ino; scalar_t__ st_dev; scalar_t__ st_flags; scalar_t__ st_gen; TYPE_3__ st_birthtim; TYPE_2__ st_mtim; TYPE_1__ st_ctim; } ;
typedef  TYPE_4__ uv_stat_t ;

/* Variables and functions */

__attribute__((used)) static int statbuf_eq(const uv_stat_t* a, const uv_stat_t* b) {
  return a->st_ctim.tv_nsec == b->st_ctim.tv_nsec
      && a->st_mtim.tv_nsec == b->st_mtim.tv_nsec
      && a->st_birthtim.tv_nsec == b->st_birthtim.tv_nsec
      && a->st_ctim.tv_sec == b->st_ctim.tv_sec
      && a->st_mtim.tv_sec == b->st_mtim.tv_sec
      && a->st_birthtim.tv_sec == b->st_birthtim.tv_sec
      && a->st_size == b->st_size
      && a->st_mode == b->st_mode
      && a->st_uid == b->st_uid
      && a->st_gid == b->st_gid
      && a->st_ino == b->st_ino
      && a->st_dev == b->st_dev
      && a->st_flags == b->st_flags
      && a->st_gen == b->st_gen;
}
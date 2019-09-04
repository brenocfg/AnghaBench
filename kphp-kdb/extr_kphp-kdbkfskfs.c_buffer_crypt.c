#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kfs_replica_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* ctr_crypt ) (TYPE_2__*,unsigned char*,unsigned char*,int,unsigned char*,long long) ;} ;
struct TYPE_4__ {TYPE_2__* ctx_crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,unsigned char*,int,unsigned char*,long long) ; 

__attribute__((used)) static void buffer_crypt (kfs_replica_handle_t R, unsigned char *buff, long long size, unsigned char iv[16], long long off) {
  assert (R && R->ctx_crypto && size >= 0);
  if (!size) {
    return;
  }
  while (1) {
    int w = 0x7ffffff0 < size ? 0x7ffffff0 : size;
    R->ctx_crypto->ctr_crypt (R->ctx_crypto, buff, buff, w, iv, off);
    size -= w;
    if (!size) {
      break;
    }
    buff += w;
    off += w;
  }
}
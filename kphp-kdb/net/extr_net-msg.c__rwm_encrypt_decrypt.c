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
struct vk_aes_ctx {int /*<<< orphan*/  (* cbc_crypt ) (struct vk_aes_ctx*,unsigned char*,unsigned char*,int,unsigned char*) ;int /*<<< orphan*/  (* ige_crypt ) (struct vk_aes_ctx*,unsigned char*,unsigned char*,int,unsigned char*) ;} ;
struct raw_message {int total_bytes; int first_offset; int last_offset; struct msg_part* last; struct msg_part* first; } ;
struct msg_part {int offset; int len; struct msg_part* next; TYPE_1__* part; } ;
struct TYPE_2__ {unsigned char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  rwm_fork_deep (struct raw_message*) ; 
 int /*<<< orphan*/  stub1 (struct vk_aes_ctx*,void*,void*,int,unsigned char*) ; 
 int /*<<< orphan*/  stub2 (struct vk_aes_ctx*,void*,void*,int,unsigned char*) ; 
 int /*<<< orphan*/  stub3 (struct vk_aes_ctx*,unsigned char*,unsigned char*,int,unsigned char*) ; 
 int /*<<< orphan*/  stub4 (struct vk_aes_ctx*,unsigned char*,unsigned char*,int,unsigned char*) ; 

int _rwm_encrypt_decrypt (struct raw_message *raw, int bytes, struct vk_aes_ctx *ctx, int mode, unsigned char *iv) {
  assert (bytes >= 0);
  if (bytes > raw->total_bytes) {
    bytes = raw->total_bytes;
  }
  bytes &= ~15;
  if (!bytes) {
    return 0;
  }
  int s = bytes;
  rwm_fork_deep (raw);
//  assert (raw->total_bytes % 16 == 0);

  struct msg_part *mp = raw->first;
  int start = (mp == raw->first) ? raw->first_offset : mp->offset;
  int len = (mp == raw->last) ? raw->last_offset - start : mp->len + mp->offset - start;  
  while (bytes) {
    assert (start >= 0);
    assert (len >= 0);
    while (len >= 16) {
      int l = len < bytes ? (len & ~15) : bytes;
      if (!mode) {
        ctx->ige_crypt (ctx, (void *)(mp->part->data + start), (void *)(mp->part->data + start), l, iv);
      } else {
        ctx->cbc_crypt (ctx, (void *)(mp->part->data + start), (void *)(mp->part->data + start), l, iv);
      }
      start += l;
      bytes -= l;
      len = len & 15;
    }
    if (len && bytes) {
      static unsigned char c[16];
      int p = 0;
      int _len = len;
      int _start = start;
      struct msg_part *_mp = mp;
      while (p < 16) {
        int x = (len > 16 - p) ? 16 - p : len;
        memcpy (c + p, mp->part->data + start, x);
        p += x;        
        if (len == x) {
          mp = mp->next;
          if (mp) {
            start = mp->offset;
            len = (mp == raw->last) ? raw->last_offset - start : mp->len;
          } else {
            start = -1;
            len = -1;
            assert (p == 16);
          }
        } else {
          break;
        }
      }
      if (!mode) {
        ctx->ige_crypt (ctx, c, c, 16, iv);
      } else {
        ctx->cbc_crypt (ctx, c, c, 16, iv);
      }
      len = _len;
      start = _start;
      mp = _mp;
      p = 0;
      while (p < 16) {
        int x = (len > 16 - p) ? 16 - p : len;
        memcpy (mp->part->data + start, c + p, x);
        p += x;        
        if (len == x) {
          mp = mp->next;
          if (mp) {
            start = mp->offset;
            len = (mp == raw->last) ? raw->last_offset - start : mp->len;
          } else {
            start = -1;
            len = -1;
            assert (p == 16);
          }
        } else {
          start += x;
          len -= x;
          break;
        }
      }
      bytes -= 16;
    } else {
      mp = mp->next;
      if (mp) {
        start = mp->offset;
        len = (mp == raw->last) ? raw->last_offset - start : mp->len;
      } else {
        start = -1;
        len = -1;
      }
    }    
  }
//  assert (!mp || (raw->last->next == mp) || (mp == raw->last && start == raw->last_offset && !len));
  return s;
}
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
typedef  int /*<<< orphan*/  t ;
struct vk_aes_ctx {int dummy; } ;
struct process_id {int /*<<< orphan*/  utime; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {scalar_t__ h_idx; } ;
struct udp_target {int flags; long long hash; int generation; int received_prefix; unsigned char* ipv6; scalar_t__ window_size; int /*<<< orphan*/  window_queue; scalar_t__ socket; int /*<<< orphan*/  port; struct process_id PID; struct vk_aes_ctx aes_ctx_enc; scalar_t__ aes_ctx_initialized; struct tree_int* confirm_tree; int /*<<< orphan*/  unack_size; TYPE_1__ confirm_timer; scalar_t__ last_ack; } ;
struct raw_message {int total_bytes; } ;
struct udp_message {int* ipv6; struct raw_message raw; scalar_t__ our_ip_idx; int /*<<< orphan*/  port; scalar_t__ next; } ;
struct tree_int {int dummy; } ;
struct tmp_msg {scalar_t__ value_bytes; struct udp_message* msg; } ;
struct aes_key_data {int /*<<< orphan*/  write_key; } ;

/* Variables and functions */
 struct process_id PID ; 
 int* R ; 
 int Rpos ; 
 scalar_t__ STOP_WINDOW_SIZE ; 
 int TL_NET_UDP_PACKET_UNENC_HEADER ; 
 int UDP_ALLOW_ENC ; 
 int UDP_CRYPTO_AES ; 
 int UDP_CRYPTO_NONE ; 
 int UDP_PROTO_VERSION ; 
 int UDP_WAIT ; 
 int /*<<< orphan*/  __dump_R ; 
 int /*<<< orphan*/  aes_create_udp_keys (struct aes_key_data*,struct process_id*,struct process_id*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ default_udp_socket ; 
 scalar_t__ drand48 () ; 
 int /*<<< orphan*/  free (struct udp_message*) ; 
 int get_crypto_key_id () ; 
 int lrand48 () ; 
 struct udp_message* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,...) ; 
 int /*<<< orphan*/  memset (struct vk_aes_ctx*,int /*<<< orphan*/ ,int) ; 
 int now ; 
 scalar_t__ out_buf_bytes ; 
 int out_buf_first_int ; 
 scalar_t__ out_buf_init ; 
 struct raw_message out_buf_msg ; 
 int out_buf_next ; 
 int out_buf_packets ; 
 int out_buf_prev ; 
 scalar_t__ out_buf_size ; 
 int out_buf_start ; 
 struct udp_target* out_buf_target ; 
 int /*<<< orphan*/  queue_add_tmp_msg (int /*<<< orphan*/ ,struct tmp_msg) ; 
 unsigned int rwm_crc32c (struct raw_message*,int) ; 
 int /*<<< orphan*/  rwm_create (struct raw_message*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwm_dump (struct raw_message*) ; 
 int rwm_encrypt_decrypt (struct raw_message*,int,struct vk_aes_ctx*,unsigned char*) ; 
 int /*<<< orphan*/  rwm_free (struct raw_message*) ; 
 int rwm_push_data (struct raw_message*,...) ; 
 int rwm_push_data_front (struct raw_message*,int*,int) ; 
 int /*<<< orphan*/  start_confirm_timer (struct udp_target*) ; 
 int /*<<< orphan*/  stop_confirm_timer (struct udp_target*) ; 
 int /*<<< orphan*/  tree_act_int (struct tree_int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_clear_int (struct tree_int*) ; 
 int /*<<< orphan*/  tree_count_int (struct tree_int*) ; 
 int /*<<< orphan*/  tree_split_int (struct tree_int**,struct tree_int**,struct tree_int*,int) ; 
 int /*<<< orphan*/  udp_data_body_sent ; 
 int /*<<< orphan*/  udp_data_sent ; 
 scalar_t__ udp_drop_probability ; 
 int /*<<< orphan*/  udp_encrypted_packets_sent ; 
 int /*<<< orphan*/  udp_packets_sent ; 
 int /*<<< orphan*/  udp_queue_message (scalar_t__,struct udp_message*) ; 
 int /*<<< orphan*/  udp_unencrypted_packets_sent ; 
 int verbosity ; 
 int /*<<< orphan*/  vk_aes_set_encrypt_key (struct vk_aes_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

void out_buf_flush (int force) {
  static int head[100];
  static int mid[100];
  static int tail[100];
  int head_pos = 0;
  int mid_pos = 0;
  int tail_pos = 0;

  head[head_pos ++] = TL_NET_UDP_PACKET_UNENC_HEADER;
  head[head_pos ++] = 0;

  struct udp_target *S = out_buf_target;
  int encr = get_crypto_key_id () != 0 && ((S->flags & UDP_ALLOW_ENC));
  int *flags = head + 1;

  if (out_buf_target->last_ack) {
    head[1] |= 4;
    *(long long *)(head + head_pos) = S->hash;
    head_pos += 2;
  } else {
    head[1] |= 1;
    struct process_id *pp = (void *)(head + head_pos);
    pp[0] = PID;
    pp[1] = S->PID;
    head_pos += 6;
    head[1] |= 8;
    head[head_pos ++] = S->generation;
    if (encr) {
      head[head_pos++] = UDP_CRYPTO_AES | 128 | ((get_crypto_key_id () & 0xfff) << 8);
    } else {
      head[head_pos++] = UDP_CRYPTO_NONE | 128;
    }
  }

  if (encr) {
    head[1] |= 128;
    flags = mid;
    *flags = 0;
    mid_pos ++;
  }

  if (!S->PID.pid || !S->PID.utime) {
    *flags |= 512;
    mid[mid_pos ++] = now;
  }

  if (!S->last_ack) {
    *flags |= 1024;
    mid[mid_pos ++] = (1 << 16) + (UDP_PROTO_VERSION);
  }

  if (S->confirm_tree) {
    if (S->confirm_timer.h_idx) {
      stop_confirm_timer (S);
    }
    Rpos = 0;
    tree_act_int (S->confirm_tree, __dump_R);
    int p = 0;
    if (R[0] <= S->received_prefix) {
      (*flags) |= (1 << 13);
      mid[mid_pos ++] = S->received_prefix;
      vkprintf (4, "Confirmed up to %d\n", R[0]);
    }
    while (p < Rpos && R[p] <= S->received_prefix) { p ++; }
    if (p < Rpos) {
      int o = p;
      while (p < Rpos && R[p] == R[p - 1] + 1) { p ++; }
      if (p - o > 1) {
        (*flags) |= (1 << 14);
        mid[mid_pos ++] = R[o];
        mid[mid_pos ++] = R[p - 1];
      } else {
        p = o;
      }
    }
    if (p < Rpos) {
      int x = Rpos - p;
      if (x > 50) { x = 50; }
      (*flags) |= (1 << 15);
      mid[mid_pos ++] = x;
      memcpy (mid + mid_pos, R + p, x * 4);
      mid_pos += x;
      p += x;
      int i;
      for (i = 0; i < Rpos; i++) {
        vkprintf (4, "Confirmed %d\n", R[p - x + i]);
      }
      
    }
    struct tree_int *L, *RR;
    tree_split_int (&L, &RR, S->confirm_tree, R[p - 1]);
    S->confirm_tree = RR;
    tree_clear_int (L);
    if (RR) {
      start_confirm_timer (S);
    }
    S->unack_size = tree_count_int (S->confirm_tree);
  }

  assert (out_buf_packets >= 0);
  if (out_buf_packets == 0) {
  } else  if (out_buf_packets == 1) {
    (*flags) |= (1 << 20);
    mid[mid_pos ++] = out_buf_start;
  } else {
    (*flags) |= (1 << 21);
    mid[mid_pos ++] = out_buf_start;
    mid[mid_pos ++] = out_buf_packets;
  }

  if (out_buf_prev) {
    (*flags) |= (1 << 22);
    mid[mid_pos ++] = out_buf_prev;
  }
  if (out_buf_next) {
    (*flags) |= (1 << 23);
    mid[mid_pos ++] = out_buf_next;
  }

  if (out_buf_packets == 0) {
  } else if (out_buf_packets == 1) {
    (*flags) |= (1 << 26);
  } else {
    (*flags) |= (1 << 27);
    mid[mid_pos ++] = out_buf_first_int;
  }

  int len = mid_pos + tail_pos + (out_buf_init ? (out_buf_msg.total_bytes >> 2) : 0);
  if (encr) {
    len += (head_pos - 2);
  }
  if (len & 1) {
    (*flags) |= (1 << 28);
    tail[tail_pos ++] = 0;
    len ++;
  }
  if (len & 2) {
    (*flags) |= (1 << 29);
    *(long long *)(tail + tail_pos) = 0;
    tail_pos += 2;
    len += 2;
  }

  if (encr) {
    memcpy (tail + tail_pos, head + 2, (head_pos - 2) * 4);
    tail_pos += (head_pos - 2);
  }
 

  struct vk_aes_ctx *enc = 0; 
  static unsigned char out[32];
  if (encr) {
    if (S->aes_ctx_initialized) {
      enc = &S->aes_ctx_enc;      
    } else {
      static struct vk_aes_ctx t;
      enc = &t;
      memset (enc, 0, sizeof (t));
      static struct aes_key_data A;
      aes_create_udp_keys (&A, &PID, &S->PID, S->generation);
      vk_aes_set_encrypt_key (enc, A.write_key, 256); 
    }
    head[1] |= 16;    
    head[1] |= 32;
    *flags |= (head[1] & 127);
  }
  if (!out_buf_init) {
    rwm_create (&out_buf_msg, 0, 0);
  }
  struct raw_message *z = &out_buf_msg;  
  assert (rwm_push_data_front (z, mid, mid_pos * 4) == mid_pos * 4);
  assert (rwm_push_data (z, tail, tail_pos * 4) == tail_pos * 4);

  if (encr) {
    int i;
#ifdef USE_SHA1
    assert (rwm_sha1 (&m, m.total_bytes, out) == m.total_bytes);
#else
    for (i = 0; i < 4; i++) {
      *(int *)(out + 4 * i) = lrand48 ();
    }
#endif
    memcpy (head + head_pos, out, 16);
    head_pos += 4;
    for (i = 0; i < 4; i++) {
      int t = lrand48 ();
      *(int *)(out + 16 + 4 * i) = t;
      head[head_pos ++] = t;
    }
    assert (z->total_bytes % 16 == 0);
    assert (rwm_encrypt_decrypt (z, z->total_bytes, enc, out) == z->total_bytes);
  }

  assert (rwm_push_data_front (z, head, head_pos * 4) == head_pos * 4);

  unsigned crc32c = rwm_crc32c (z, z->total_bytes);
  assert (rwm_push_data (z, &crc32c, 4) == 4);

  if (verbosity >= 3) {
    rwm_dump (z);
  }

  struct udp_message *a = malloc (sizeof (*a));
  a->raw = *z;
  a->next = 0;
  memcpy (a->ipv6, S->ipv6, 16);
  a->port = S->port;
  a->our_ip_idx = 0;

  if (force || !(S->flags & UDP_WAIT)) {
    udp_packets_sent ++;
    udp_data_sent += a->raw.total_bytes;
    udp_data_body_sent += out_buf_bytes;
    if (udp_drop_probability && drand48 () < udp_drop_probability) {
      //vkprintf (0, "Dropped\n");
      rwm_free (&a->raw);
      free (a);    
    } else {
      udp_queue_message (S->socket ? S->socket : default_udp_socket, a);
    }
    if (!force) {
      S->window_size += out_buf_bytes;
      if (S->window_size >= STOP_WINDOW_SIZE) {
        //vkprintf (0, "WINDOW START\n");
        S->flags |= UDP_WAIT;
      }
    }
  } else {
    struct tmp_msg x = {
      .msg = a,
      .value_bytes = out_buf_bytes
    };
    S->window_queue = queue_add_tmp_msg (S->window_queue, x);
  }

  if (encr) {
    udp_encrypted_packets_sent ++;
  } else {
    udp_unencrypted_packets_sent ++;
  }


  out_buf_init = 0;
  out_buf_size = 0;
  out_buf_prev = 0;
  out_buf_next = 0;
  out_buf_packets = 0;
  out_buf_bytes = 0;
}
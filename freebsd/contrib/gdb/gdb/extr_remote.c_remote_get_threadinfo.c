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
typedef  int /*<<< orphan*/  threadref ;
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;
struct gdb_ext_thread_info {int dummy; } ;

/* Variables and functions */
 char* alloca (int /*<<< orphan*/ ) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_threadinfo_request (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int remote_unpack_thread_info_response (char*,int /*<<< orphan*/ *,struct gdb_ext_thread_info*) ; 

__attribute__((used)) static int
remote_get_threadinfo (threadref *threadid, int fieldset,	/* TAG mask */
		       struct gdb_ext_thread_info *info)
{
  struct remote_state *rs = get_remote_state ();
  int result;
  char *threadinfo_pkt = alloca (rs->remote_packet_size);

  pack_threadinfo_request (threadinfo_pkt, fieldset, threadid);
  putpkt (threadinfo_pkt);
  getpkt (threadinfo_pkt, (rs->remote_packet_size), 0);
  result = remote_unpack_thread_info_response (threadinfo_pkt + 2, threadid,
					       info);
  return result;
}
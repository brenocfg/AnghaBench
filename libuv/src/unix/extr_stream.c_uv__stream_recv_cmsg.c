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
struct TYPE_4__ {int accepted_fd; } ;
typedef  TYPE_1__ uv_stream_t ;
struct msghdr {int dummy; } ;
struct cmsghdr {scalar_t__ cmsg_type; int cmsg_len; } ;

/* Variables and functions */
 void* CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 int CMSG_LEN (unsigned int) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 scalar_t__ SCM_RIGHTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int uv__stream_queue_fd (TYPE_1__*,int) ; 

__attribute__((used)) static int uv__stream_recv_cmsg(uv_stream_t* stream, struct msghdr* msg) {
  struct cmsghdr* cmsg;

  for (cmsg = CMSG_FIRSTHDR(msg); cmsg != NULL; cmsg = CMSG_NXTHDR(msg, cmsg)) {
    char* start;
    char* end;
    int err;
    void* pv;
    int* pi;
    unsigned int i;
    unsigned int count;

    if (cmsg->cmsg_type != SCM_RIGHTS) {
      fprintf(stderr, "ignoring non-SCM_RIGHTS ancillary data: %d\n",
          cmsg->cmsg_type);
      continue;
    }

    /* silence aliasing warning */
    pv = CMSG_DATA(cmsg);
    pi = pv;

    /* Count available fds */
    start = (char*) cmsg;
    end = (char*) cmsg + cmsg->cmsg_len;
    count = 0;
    while (start + CMSG_LEN(count * sizeof(*pi)) < end)
      count++;
    assert(start + CMSG_LEN(count * sizeof(*pi)) == end);

    for (i = 0; i < count; i++) {
      /* Already has accepted fd, queue now */
      if (stream->accepted_fd != -1) {
        err = uv__stream_queue_fd(stream, pi[i]);
        if (err != 0) {
          /* Close rest */
          for (; i < count; i++)
            uv__close(pi[i]);
          return err;
        }
      } else {
        stream->accepted_fd = pi[i];
      }
    }
  }

  return 0;
}
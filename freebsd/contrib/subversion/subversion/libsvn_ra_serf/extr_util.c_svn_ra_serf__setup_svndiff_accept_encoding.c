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
struct TYPE_4__ {scalar_t__ using_compression; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_headers_setn (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ svn_ra_serf__is_low_latency_connection (TYPE_1__*) ; 
 scalar_t__ svn_tristate_false ; 
 scalar_t__ svn_tristate_unknown ; 

void
svn_ra_serf__setup_svndiff_accept_encoding(serf_bucket_t *headers,
                                           svn_ra_serf__session_t *session)
{
  if (session->using_compression == svn_tristate_false)
    {
      /* Don't advertise support for compressed svndiff formats if
         compression is disabled. */
      serf_bucket_headers_setn(
        headers, "Accept-Encoding", "svndiff");
    }
  else if (session->using_compression == svn_tristate_unknown &&
           svn_ra_serf__is_low_latency_connection(session))
    {
      /* With http-compression=auto, advertise that we prefer svndiff2
         to svndiff1 with a low latency connection (assuming the underlying
         network has high bandwidth), as it is faster and in this case, we
         don't care about worse compression ratio. */
      serf_bucket_headers_setn(
        headers, "Accept-Encoding",
        "gzip,svndiff2;q=0.9,svndiff1;q=0.8,svndiff;q=0.7");
    }
  else
    {
      /* Otherwise, advertise that we prefer svndiff1 over svndiff2.
         svndiff2 is not a reasonable substitute for svndiff1 with default
         compression level, because, while it is faster, it also gives worse
         compression ratio.  While we can use svndiff2 in some cases (see
         above), we can't do this generally. */
      serf_bucket_headers_setn(
        headers, "Accept-Encoding",
        "gzip,svndiff1;q=0.9,svndiff2;q=0.8,svndiff;q=0.7");
    }
}
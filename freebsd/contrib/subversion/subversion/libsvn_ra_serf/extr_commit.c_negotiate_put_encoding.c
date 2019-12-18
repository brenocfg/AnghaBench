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
struct TYPE_4__ {scalar_t__ using_compression; scalar_t__ supports_svndiff2; scalar_t__ supports_svndiff1; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;

/* Variables and functions */
 int SVN_DELTA_COMPRESSION_LEVEL_DEFAULT ; 
 int SVN_DELTA_COMPRESSION_LEVEL_NONE ; 
 scalar_t__ svn_ra_serf__is_low_latency_connection (TYPE_1__*) ; 
 scalar_t__ svn_tristate_true ; 
 scalar_t__ svn_tristate_unknown ; 

__attribute__((used)) static void
negotiate_put_encoding(int *svndiff_version_p,
                       int *svndiff_compression_level_p,
                       svn_ra_serf__session_t *session)
{
  int svndiff_version;
  int compression_level;

  if (session->using_compression == svn_tristate_unknown)
    {
      /* With http-compression=auto, prefer svndiff2 to svndiff1 with a
       * low latency connection (assuming the underlying network has high
       * bandwidth), as it is faster and in this case, we don't care about
       * worse compression ratio.
       *
       * Note: For future compatibility, we also handle a theoretically
       * possible case where the server has advertised only svndiff2 support.
       */
      if (session->supports_svndiff2 &&
          svn_ra_serf__is_low_latency_connection(session))
        svndiff_version = 2;
      else if (session->supports_svndiff1)
        svndiff_version = 1;
      else if (session->supports_svndiff2)
        svndiff_version = 2;
      else
        svndiff_version = 0;
    }
  else if (session->using_compression == svn_tristate_true)
    {
      /* Otherwise, prefer svndiff1, as svndiff2 is not a reasonable
       * substitute for svndiff1 with default compression level.  (It gives
       * better speed and compression ratio comparable to svndiff1 with
       * compression level 1, but not 5).
       *
       * Note: For future compatibility, we also handle a theoretically
       * possible case where the server has advertised only svndiff2 support.
       */
      if (session->supports_svndiff1)
        svndiff_version = 1;
      else if (session->supports_svndiff2)
        svndiff_version = 2;
      else
        svndiff_version = 0;
    }
  else
    {
      /* Difference between svndiff formats 0 and 1/2 that format 1/2 allows
       * compression.  Uncompressed svndiff0 should also be slightly more
       * effective if the compression is not required at all.
       *
       * If the server cannot handle svndiff1/2, or compression is disabled
       * with the 'http-compression = no' client configuration option, fall
       * back to uncompressed svndiff0 format.  As a bonus, users can force
       * the usage of the uncompressed format by setting the corresponding
       * client configuration option, if they want to.
       */
      svndiff_version = 0;
    }

  if (svndiff_version == 0)
    compression_level = SVN_DELTA_COMPRESSION_LEVEL_NONE;
  else
    compression_level = SVN_DELTA_COMPRESSION_LEVEL_DEFAULT;

  *svndiff_version_p = svndiff_version;
  *svndiff_compression_level_p = compression_level;
}
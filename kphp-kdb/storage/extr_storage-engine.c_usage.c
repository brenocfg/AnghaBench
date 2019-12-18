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

/* Variables and functions */
 char* FullVersionStr ; 
 int aio_query_timeout_value ; 
 char* bad_image_cache_max_living_time ; 
 int /*<<< orphan*/  choose_binlog_options ; 
 int /*<<< orphan*/  exit (int) ; 
 int max_immediately_reply_filesize ; 
 int max_metafiles_bytes ; 
 int max_zmalloc_bytes ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int,int,int,int,int,char*,int /*<<< orphan*/ ) ; 
 char* progname ; 
 int required_volumes_at_startup ; 

void usage (void) {
  printf ("usage: %s [-v] [-r] [-i] [-p<port>] [-H<http-port>] [-n<nginx-port>] [-u<username>] [-g<groupname>] [-c<max-conn>] <binlogs-dirname>]\n"
    "\t%s\n"
	  "\t-i\tindex mode (docs bodies only in binlog)\n"
	  "\t-I<volume_id>\tsingle volume index mode\n"
	  "\t-v\toutput statistical and debug information into stderr\n"
	  "\t-r\tread-only binlog (don't log new events)\n"
    "\t-R<filesize>\tsets max_immediately_reply_filesize, could be end by 'k', 'm', etc. (default: %d)\n"
    "\t-M<max_metafiles_size>\tcould be end by 'k', 'm', etc. (default: %d)\n"
    "\t-Z<max_zmalloc_memory>\tcould be end by 'k', 'm', etc. (default: %d)\n"
    "\t\tzmalloc memory used only for aio_connections\n"
    "\t-T<aio_query_timeout>\tset aio query timeout (default: %.3lf)\n"
    "\t-F\tdisable crc32 check after loading metafile\n"
    "\t-V<required-volumes-number-at-startup>\t(default: %d)\n"
    "\t-L<bad-image-cache-max_living-time>\t(default: %ds)\n"
    "\t-A<max_aio_read_connection>\tlimit number of aio read connection for one disk (default: 0 - no limit)\n"
    "\t-C<choose_binlog_criterions>\t(default: '%s')\n"
    "\t\t\t's' - minimal consecutive file failures,\n"
    "\t\t\t'a' - minimal aio read connections for disk,\n"
    "\t\t\t'h' - minimal amortization hour file failures,\n"
    "\t\t\t't' - minimal total file failures)\n"
    "\t-E<N,cs,md5_mode,prefix>\tcreate N empty binlogs and write config-file\n"
    "\t\t\t\t(volume_id = cs * 1000 + log_split_min)\n",
	  progname,
    FullVersionStr,
    max_immediately_reply_filesize,
    max_metafiles_bytes, max_zmalloc_bytes, aio_query_timeout_value, required_volumes_at_startup, bad_image_cache_max_living_time, choose_binlog_options);
  exit (2);
}
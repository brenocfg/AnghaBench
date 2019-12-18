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
struct remote_state {int remote_packet_size; } ;
struct gdb_ext_thread_info {char* display; char* shortname; char* more_display; int /*<<< orphan*/  active; int /*<<< orphan*/  threadid; } ;

/* Variables and functions */
 unsigned int TAG_DISPLAY ; 
 unsigned int TAG_EXISTS ; 
 unsigned int TAG_MOREDISPLAY ; 
 unsigned int TAG_THREADID ; 
 unsigned int TAG_THREADNAME ; 
 int /*<<< orphan*/  copy_threadref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  stub_unpack_int (char*,int) ; 
 int /*<<< orphan*/  threadmatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* unpack_byte (char*,int*) ; 
 char* unpack_int (char*,...) ; 
 char* unpack_string (char*,char*,int) ; 
 char* unpack_threadid (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static int
remote_unpack_thread_info_response (char *pkt, threadref *expectedref,
				    struct gdb_ext_thread_info *info)
{
  struct remote_state *rs = get_remote_state ();
  int mask, length;
  unsigned int tag;
  threadref ref;
  char *limit = pkt + (rs->remote_packet_size);	/* plausable parsing limit */
  int retval = 1;

  /* info->threadid = 0; FIXME: implement zero_threadref */
  info->active = 0;
  info->display[0] = '\0';
  info->shortname[0] = '\0';
  info->more_display[0] = '\0';

  /* Assume the characters indicating the packet type have been stripped */
  pkt = unpack_int (pkt, &mask);	/* arg mask */
  pkt = unpack_threadid (pkt, &ref);

  if (mask == 0)
    warning ("Incomplete response to threadinfo request\n");
  if (!threadmatch (&ref, expectedref))
    {				/* This is an answer to a different request */
      warning ("ERROR RMT Thread info mismatch\n");
      return 0;
    }
  copy_threadref (&info->threadid, &ref);

  /* Loop on tagged fields , try to bail if somthing goes wrong */

  while ((pkt < limit) && mask && *pkt)		/* packets are terminated with nulls */
    {
      pkt = unpack_int (pkt, &tag);	/* tag */
      pkt = unpack_byte (pkt, &length);		/* length */
      if (!(tag & mask))	/* tags out of synch with mask */
	{
	  warning ("ERROR RMT: threadinfo tag mismatch\n");
	  retval = 0;
	  break;
	}
      if (tag == TAG_THREADID)
	{
	  if (length != 16)
	    {
	      warning ("ERROR RMT: length of threadid is not 16\n");
	      retval = 0;
	      break;
	    }
	  pkt = unpack_threadid (pkt, &ref);
	  mask = mask & ~TAG_THREADID;
	  continue;
	}
      if (tag == TAG_EXISTS)
	{
	  info->active = stub_unpack_int (pkt, length);
	  pkt += length;
	  mask = mask & ~(TAG_EXISTS);
	  if (length > 8)
	    {
	      warning ("ERROR RMT: 'exists' length too long\n");
	      retval = 0;
	      break;
	    }
	  continue;
	}
      if (tag == TAG_THREADNAME)
	{
	  pkt = unpack_string (pkt, &info->shortname[0], length);
	  mask = mask & ~TAG_THREADNAME;
	  continue;
	}
      if (tag == TAG_DISPLAY)
	{
	  pkt = unpack_string (pkt, &info->display[0], length);
	  mask = mask & ~TAG_DISPLAY;
	  continue;
	}
      if (tag == TAG_MOREDISPLAY)
	{
	  pkt = unpack_string (pkt, &info->more_display[0], length);
	  mask = mask & ~TAG_MOREDISPLAY;
	  continue;
	}
      warning ("ERROR RMT: unknown thread info tag\n");
      break;			/* Not a tag we know about */
    }
  return retval;
}
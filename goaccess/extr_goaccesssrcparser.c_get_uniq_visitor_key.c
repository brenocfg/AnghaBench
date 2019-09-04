#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* host; char* date; int /*<<< orphan*/  agent; } ;
typedef  TYPE_1__ GLogItem ;

/* Variables and functions */
 char* deblank (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 
 char* xcalloc (size_t,int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
get_uniq_visitor_key (GLogItem * logitem)
{
  char *ua = NULL, *key = NULL;
  size_t s1, s2, s3;

  ua = deblank (xstrdup (logitem->agent));

  s1 = strlen (logitem->host);
  s2 = strlen (logitem->date);
  s3 = strlen (ua);

  /* includes terminating null */
  key = xcalloc (s1 + s2 + s3 + 3, sizeof (char));

  memcpy (key, logitem->host, s1);

  key[s1] = '|';
  memcpy (key + s1 + 1, logitem->date, s2 + 1);

  key[s1 + s2 + 1] = '|';
  memcpy (key + s1 + s2 + 2, ua, s3 + 1);

  free (ua);
  return key;
}
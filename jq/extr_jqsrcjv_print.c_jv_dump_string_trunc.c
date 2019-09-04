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
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  jv_dump_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

char *jv_dump_string_trunc(jv x, char *outbuf, size_t bufsize) {
  x = jv_dump_string(x,0);
  const char* p = jv_string_value(x);
  const size_t len = strlen(p);
  strncpy(outbuf, p, bufsize);
  outbuf[bufsize - 1] = 0;
  if (len > bufsize - 1 && bufsize >= 4) {
    // Indicate truncation with '...'
    outbuf[bufsize - 2]='.';
    outbuf[bufsize - 3]='.';
    outbuf[bufsize - 4]='.';
  }
  jv_free(x);
  return outbuf;
}
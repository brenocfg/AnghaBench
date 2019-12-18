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
struct TYPE_2__ {scalar_t__ double_decode; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  decode_hex (char*,char*) ; 
 int /*<<< orphan*/  strip_newlines (char*) ; 
 char* trim_str (char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
decode_url (char *url)
{
  char *out, *decoded;

  if ((url == NULL) || (*url == '\0'))
    return NULL;

  out = decoded = xstrdup (url);
  decode_hex (url, out);
  /* double encoded URL? */
  if (conf.double_decode)
    decode_hex (decoded, out);
  strip_newlines (out);

  return trim_str (out);
}
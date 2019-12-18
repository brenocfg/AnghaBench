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
 size_t ROUNDUP (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 

__attribute__((used)) static size_t
memcpy_roundup(char *cp, const void *data, size_t len)
{
  size_t padlen;

  padlen = ROUNDUP(len);
  memcpy(cp, data, len);
  if (padlen > len)
    memset(cp + len, '\0', padlen - len);

  return padlen;
}
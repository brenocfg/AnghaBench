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
 int UV_ENOSYS ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  once ; 
 scalar_t__ uv__getentropy (char*,size_t) ; 
 int /*<<< orphan*/  uv__random_getentropy_init ; 
 int /*<<< orphan*/  uv_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv__random_getentropy(void* buf, size_t buflen) {
  size_t pos;
  size_t stride;

  uv_once(&once, uv__random_getentropy_init);

  if (uv__getentropy == NULL)
    return UV_ENOSYS;

  /* getentropy() returns an error for requests > 256 bytes. */
  for (pos = 0, stride = 256; pos + stride < buflen; pos += stride)
    if (uv__getentropy((char *) buf + pos, stride))
      return UV__ERR(errno);

  if (uv__getentropy((char *) buf + pos, buflen - pos))
    return UV__ERR(errno);

  return 0;
}
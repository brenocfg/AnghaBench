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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {char* buf; int len; } ;
typedef  TYPE_1__ out_t ;

/* Variables and functions */
 int HCBUFSIZ_SMALL ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,int const) ; 
 int /*<<< orphan*/  out_flush (TYPE_1__*) ; 

__attribute__((used)) static void out_push (out_t *out, const u8 *pw_buf, const int pw_len)
{
  char *ptr = out->buf + out->len;

  memcpy (ptr, pw_buf, pw_len);

  #if defined (_WIN)

  ptr[pw_len + 0] = '\r';
  ptr[pw_len + 1] = '\n';

  out->len += pw_len + 2;

  #else

  ptr[pw_len] = '\n';

  out->len += pw_len + 1;

  #endif

  if (out->len >= HCBUFSIZ_SMALL - 300)
  {
    out_flush (out);
  }
}
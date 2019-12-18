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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int RSTRING_LEN (int /*<<< orphan*/ ) ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_buf_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mrb_str_buf_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char) ; 

__attribute__((used)) static mrb_value
digest2hexdigest(mrb_state *mrb, mrb_value b)
{
  mrb_value h;
  int i, len;
  char *bp, buf[3];

  bp = RSTRING_PTR(b);
  len = RSTRING_LEN(b);
  h = mrb_str_buf_new(mrb, len * 2);
  for (i = 0; i < len; i++) {
    snprintf(buf, sizeof(buf), "%02x", (unsigned char )bp[i]);
    mrb_str_buf_cat(mrb, h, buf, 2);
  }
  return h;
}
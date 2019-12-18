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
typedef  TYPE_1__* wi_t ;
typedef  int /*<<< orphan*/  wi_status ;
struct TYPE_4__ {int /*<<< orphan*/  (* on_error ) (TYPE_1__*,char*,char const,char const,char const,char const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 size_t MAX_BODY_LENGTH ; 
 int /*<<< orphan*/  TO_CHAR (char const) ; 
 int /*<<< orphan*/  WI_ERROR ; 
 int /*<<< orphan*/  WI_SUCCESS ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,char const,char const,char const,char const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

wi_status wi_parse_length(wi_t self, const char *buf, size_t *to_length) {
  if (!buf || !to_length) {
    return WI_ERROR;
  }
  *to_length = (
      ((((unsigned char) buf[0]) & 0xFF) << 24) |
      ((((unsigned char) buf[1]) & 0xFF) << 16) |
      ((((unsigned char) buf[2]) & 0xFF) << 8) |
      (((unsigned char) buf[3]) & 0xFF));
  if (MAX_BODY_LENGTH > 0 && *to_length > MAX_BODY_LENGTH) {
#define TO_CHAR(c) ((c) >= ' ' && (c) < '~' ? (c) : '.')
    return self->on_error(self, "Invalid packet header "
        "0x%x%x%x%x == %c%c%c%c == %zd",
        buf[0], buf[1], buf[2], buf[3],
        TO_CHAR(buf[0]), TO_CHAR(buf[1]),
        TO_CHAR(buf[2]), TO_CHAR(buf[3]),
        *to_length);
  }
  return WI_SUCCESS;
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static inline void wpabuf_put_be16(struct wpabuf *buf, u16 data)
{
	u8 *pos = (u8 *) wpabuf_put(buf, 2);
	WPA_PUT_BE16(pos, data);
}
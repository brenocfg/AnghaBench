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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ wpabuf_head (struct wpabuf const*) ; 

__attribute__((used)) static inline const u8 * wpabuf_head_u8(const struct wpabuf *buf)
{
	return (const u8 *) wpabuf_head(buf);
}
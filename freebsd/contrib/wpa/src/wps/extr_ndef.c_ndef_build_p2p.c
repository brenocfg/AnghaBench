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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int FLAG_MESSAGE_BEGIN ; 
 int FLAG_MESSAGE_END ; 
 int FLAG_TNF_RFC2046 ; 
 struct wpabuf* ndef_build_record (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wpabuf const*) ; 
 int /*<<< orphan*/  os_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_handover_type ; 

struct wpabuf * ndef_build_p2p(const struct wpabuf *buf)
{
	return ndef_build_record(FLAG_MESSAGE_BEGIN | FLAG_MESSAGE_END |
				 FLAG_TNF_RFC2046, p2p_handover_type,
				 os_strlen(p2p_handover_type), NULL, 0, buf);
}
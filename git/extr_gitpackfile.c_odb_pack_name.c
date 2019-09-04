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
struct strbuf {char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_object_directory () ; 
 int /*<<< orphan*/  sha1_to_hex (unsigned char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

char *odb_pack_name(struct strbuf *buf,
		    const unsigned char *sha1,
		    const char *ext)
{
	strbuf_reset(buf);
	strbuf_addf(buf, "%s/pack/pack-%s.%s", get_object_directory(),
		    sha1_to_hex(sha1), ext);
	return buf->buf;
}
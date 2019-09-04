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
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 void* strbuf_detach (struct strbuf*,size_t*) ; 

__attribute__((used)) static void *anonymize_path_component(const void *path, size_t *len)
{
	static int counter;
	struct strbuf out = STRBUF_INIT;
	strbuf_addf(&out, "path%d", counter++);
	return strbuf_detach(&out, len);
}
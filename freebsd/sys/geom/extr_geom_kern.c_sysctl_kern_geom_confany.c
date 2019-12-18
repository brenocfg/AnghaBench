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
struct sysctl_req {size_t oldidx; int /*<<< orphan*/ * oldptr; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  g_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 size_t PAGE_SIZE ; 
 int SBUF_AUTOEXTEND ; 
 int SBUF_FIXEDLEN ; 
 int SBUF_INCLUDENUL ; 
 int SYSCTL_OUT (struct sysctl_req*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  g_waitfor_event (int /*<<< orphan*/ *,struct sbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_count_drain ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 size_t sbuf_len (struct sbuf*) ; 
 struct sbuf* sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  sbuf_set_drain (struct sbuf*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
sysctl_kern_geom_confany(struct sysctl_req *req, g_event_t *func, size_t *hint)
{
	size_t len = 0;
	int error = 0;
	struct sbuf *sb;

	if (req->oldptr == NULL) {
		sb = sbuf_new(NULL, NULL, PAGE_SIZE, SBUF_FIXEDLEN |
		    SBUF_INCLUDENUL);
		sbuf_set_drain(sb, sbuf_count_drain, &len);
		g_waitfor_event(func, sb, M_WAITOK, NULL);
		req->oldidx = *hint = len;
	} else {
		sb = sbuf_new(NULL, NULL, *hint, SBUF_AUTOEXTEND |
		    SBUF_INCLUDENUL);
		g_waitfor_event(func, sb, M_WAITOK, NULL);
		*hint = sbuf_len(sb);
		error = SYSCTL_OUT(req, sbuf_data(sb), sbuf_len(sb));
	}
	sbuf_delete(sb);
	return error;
}
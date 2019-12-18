#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kwsmatch {scalar_t__* size; } ;
struct TYPE_5__ {scalar_t__ rm_eo; scalar_t__ rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;
struct TYPE_6__ {unsigned long size; char* ptr; } ;
typedef  TYPE_2__ mmfile_t ;
typedef  int /*<<< orphan*/  kwset_t ;

/* Variables and functions */
 int REG_NOTBOL ; 
 size_t kwsexec (int /*<<< orphan*/ ,char const*,unsigned long,struct kwsmatch*) ; 
 int /*<<< orphan*/  regexec_buf (int /*<<< orphan*/ *,char const*,unsigned long,int,TYPE_1__*,int) ; 

__attribute__((used)) static unsigned int contains(mmfile_t *mf, regex_t *regexp, kwset_t kws)
{
	unsigned int cnt;
	unsigned long sz;
	const char *data;

	sz = mf->size;
	data = mf->ptr;
	cnt = 0;

	if (regexp) {
		regmatch_t regmatch;
		int flags = 0;

		while (sz && *data &&
		       !regexec_buf(regexp, data, sz, 1, &regmatch, flags)) {
			flags |= REG_NOTBOL;
			data += regmatch.rm_eo;
			sz -= regmatch.rm_eo;
			if (sz && *data && regmatch.rm_so == regmatch.rm_eo) {
				data++;
				sz--;
			}
			cnt++;
		}

	} else { /* Classic exact string match */
		while (sz) {
			struct kwsmatch kwsm;
			size_t offset = kwsexec(kws, data, sz, &kwsm);
			if (offset == -1)
				break;
			sz -= offset + kwsm.size[0];
			data += offset + kwsm.size[0];
			cnt++;
		}
	}
	return cnt;
}
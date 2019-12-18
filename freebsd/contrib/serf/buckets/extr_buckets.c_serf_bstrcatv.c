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
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 

char *serf_bstrcatv(serf_bucket_alloc_t *allocator, struct iovec *vec,
                    int vecs, apr_size_t *bytes_written)
{
    int i;
    apr_size_t new_len = 0;
    char *c, *newstr;

    for (i = 0; i < vecs; i++) {
        new_len += vec[i].iov_len;
    }

    /* It's up to the caller to free this memory later. */
    newstr = serf_bucket_mem_alloc(allocator, new_len);

    c = newstr;
    for (i = 0; i < vecs; i++) {
        memcpy(c, vec[i].iov_base, vec[i].iov_len);
        c += vec[i].iov_len;
    }

    if (bytes_written) {
        *bytes_written = c - newstr;
    }

    return newstr;
}
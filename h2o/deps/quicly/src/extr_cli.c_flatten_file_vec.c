#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_3__ {scalar_t__ cbdata; } ;
typedef  TYPE_1__ quicly_sendbuf_vec_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int QUICLY_TRANSPORT_ERROR_INTERNAL ; 
 scalar_t__ errno ; 
 int pread (int,void*,size_t,size_t) ; 

__attribute__((used)) static int flatten_file_vec(quicly_sendbuf_vec_t *vec, void *dst, size_t off, size_t len)
{
    int fd = (int)vec->cbdata;
    ssize_t rret;

    /* FIXME handle partial read */
    while ((rret = pread(fd, dst, len, off)) == -1 && errno == EINTR)
        ;

    return rret == len ? 0 : QUICLY_TRANSPORT_ERROR_INTERNAL; /* should return application-level error */
}
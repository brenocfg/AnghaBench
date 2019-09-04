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
typedef  int /*<<< orphan*/  uv_loop_t ;
struct TYPE_3__ {unsigned int nbufs; int /*<<< orphan*/  off; int /*<<< orphan*/ * bufs; int /*<<< orphan*/ * bufsml; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_fs_cb ;
typedef  int /*<<< orphan*/  uv_file ;
typedef  int /*<<< orphan*/  uv_buf_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POST ; 
 int /*<<< orphan*/  READ ; 
 int UV_EINVAL ; 
 int UV_ENOMEM ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/ * uv__malloc (unsigned int) ; 

int uv_fs_read(uv_loop_t* loop, uv_fs_t* req,
               uv_file file,
               const uv_buf_t bufs[],
               unsigned int nbufs,
               int64_t off,
               uv_fs_cb cb) {
  INIT(READ);

  if (bufs == NULL || nbufs == 0)
    return UV_EINVAL;

  req->file = file;

  req->nbufs = nbufs;
  req->bufs = req->bufsml;
  if (nbufs > ARRAY_SIZE(req->bufsml))
    req->bufs = uv__malloc(nbufs * sizeof(*bufs));

  if (req->bufs == NULL)
    return UV_ENOMEM;

  memcpy(req->bufs, bufs, nbufs * sizeof(*bufs));

  req->off = off;
  POST;
}
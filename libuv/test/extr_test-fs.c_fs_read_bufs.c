#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ base; } ;
typedef  TYPE_1__ uv_buf_t ;
struct TYPE_12__ {scalar_t__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int O_RDONLY ; 
 int UV_EINVAL ; 
 TYPE_2__ close_req ; 
 scalar_t__ memcmp (scalar_t__,scalar_t__,int) ; 
 TYPE_2__ open_req1 ; 
 TYPE_2__ read_req ; 
 TYPE_1__ uv_buf_init (char*,int) ; 
 scalar_t__ uv_fs_close (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_fs_open (int /*<<< orphan*/ *,TYPE_2__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_fs_read (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_2__*) ; 

__attribute__((used)) static void fs_read_bufs(int add_flags) {
  char scratch[768];
  uv_buf_t bufs[4];

  ASSERT(0 <= uv_fs_open(NULL, &open_req1,
                         "test/fixtures/lorem_ipsum.txt",
                         O_RDONLY | add_flags, 0, NULL));
  ASSERT(open_req1.result >= 0);
  uv_fs_req_cleanup(&open_req1);

  ASSERT(UV_EINVAL == uv_fs_read(NULL, &read_req, open_req1.result,
                                 NULL, 0, 0, NULL));
  ASSERT(UV_EINVAL == uv_fs_read(NULL, &read_req, open_req1.result,
                                 NULL, 1, 0, NULL));
  ASSERT(UV_EINVAL == uv_fs_read(NULL, &read_req, open_req1.result,
                                 bufs, 0, 0, NULL));

  bufs[0] = uv_buf_init(scratch + 0, 256);
  bufs[1] = uv_buf_init(scratch + 256, 256);
  bufs[2] = uv_buf_init(scratch + 512, 128);
  bufs[3] = uv_buf_init(scratch + 640, 128);

  ASSERT(446 == uv_fs_read(NULL,
                           &read_req,
                           open_req1.result,
                           bufs + 0,
                           2,  /* 2x 256 bytes. */
                           0,  /* Positional read. */
                           NULL));
  ASSERT(read_req.result == 446);
  uv_fs_req_cleanup(&read_req);

  ASSERT(190 == uv_fs_read(NULL,
                           &read_req,
                           open_req1.result,
                           bufs + 2,
                           2,  /* 2x 128 bytes. */
                           256,  /* Positional read. */
                           NULL));
  ASSERT(read_req.result == /* 446 - 256 */ 190);
  uv_fs_req_cleanup(&read_req);

  ASSERT(0 == memcmp(bufs[1].base + 0, bufs[2].base, 128));
  ASSERT(0 == memcmp(bufs[1].base + 128, bufs[3].base, 190 - 128));

  ASSERT(0 == uv_fs_close(NULL, &close_req, open_req1.result, NULL));
  ASSERT(close_req.result == 0);
  uv_fs_req_cleanup(&close_req);
}
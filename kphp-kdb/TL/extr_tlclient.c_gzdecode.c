#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ avail_in; scalar_t__ total_out; scalar_t__ zfree; scalar_t__ zalloc; void* avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; } ;
typedef  TYPE_1__ z_stream ;
typedef  scalar_t__ uLongf ;
typedef  scalar_t__ uLong ;
typedef  void* uInt ;
typedef  scalar_t__ free_func ;
typedef  scalar_t__ alloc_func ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int Z_BUF_ERROR ; 
 int Z_DATA_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_NEED_DICT ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int inflateEnd (TYPE_1__*) ; 
 int inflateInit2 (TYPE_1__*,int) ; 

__attribute__((used)) static int gzdecode (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen) {
  z_stream stream;
  int err;
  stream.next_in = (Bytef*) source;
  stream.avail_in = (uInt) sourceLen;
  /* Check for source > 64K on 16-bit machine: */
  if ((uLong)stream.avail_in != sourceLen) return Z_BUF_ERROR;
  stream.next_out = dest;
  stream.avail_out = (uInt) *destLen;
  if ((uLong)stream.avail_out != *destLen) return Z_BUF_ERROR;
  stream.zalloc = (alloc_func) 0;
  stream.zfree = (free_func) 0;

  err = inflateInit2 (&stream, 15 + 32);
  if (err != Z_OK) {
    return err;
  }

  err = inflate (&stream, Z_FINISH);
  if (err != Z_STREAM_END) {
    inflateEnd (&stream);
    if (err == Z_NEED_DICT || (err == Z_BUF_ERROR && stream.avail_in == 0)) {
      return Z_DATA_ERROR;
    }
    return err;
  }
  *destLen = stream.total_out;

  err = inflateEnd (&stream);
  return err;
}
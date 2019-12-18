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
struct storage_data_stream {scalar_t__ bytes_read; scalar_t__ size; scalar_t__ fd; long long ptr; } ;

/* Variables and functions */
 int STORAGE_ERR_READ ; 
 int /*<<< orphan*/  memcpy (void*,long long,long long) ; 
 long long read (scalar_t__,void*,long long) ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long) ; 

__attribute__((used)) static int storage_data_stream_read (struct storage_data_stream *self, void *a, long long len) {
  vkprintf (4, "storage_data_stream_read (len: %lld)\n", len);
  if (len + self->bytes_read > self->size) {
    return STORAGE_ERR_READ;
  }
  if (self->fd >= 0) {
    if (read (self->fd, a, len) != len) {
      return STORAGE_ERR_READ;
    }
  } else {
    memcpy (a, self->ptr, len);
    self->ptr += len;
  }
  self->bytes_read += len;
  return 0;
}
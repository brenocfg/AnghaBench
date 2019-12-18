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
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int read (int,void*,size_t) ; 

__attribute__((used)) static inline ssize_t xread(int fd, void *buf, size_t count) {
  // Read some bytes. Retry on EINTR and when we don't get as many bytes as we requested.
  size_t alreadyRead = 0;
  for(;;) {
     ssize_t res = read(fd, buf, count);
     if (res == -1 && errno == EINTR) continue;
     if (res > 0) {
       buf = ((char*)buf)+res;
       count -= res;
       alreadyRead += res;
     }
     if (res == -1) return -1;
     if (count == 0 || res == 0) return alreadyRead;
  }
}
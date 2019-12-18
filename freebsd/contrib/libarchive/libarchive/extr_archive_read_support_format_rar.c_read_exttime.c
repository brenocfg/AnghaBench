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
typedef  void* time_t ;
struct tm {unsigned int tm_sec; } ;
struct rar {long mnsec; long cnsec; long ansec; long arcnsec; void* arctime; void* atime; void* ctime; void* mtime; } ;

/* Variables and functions */
 unsigned int NS_UNIT ; 
 unsigned int archive_le16dec (char const*) ; 
 int archive_le32dec (char const*) ; 
 void* get_time (int) ; 
 struct tm* localtime (void**) ; 
 void* mktime (struct tm*) ; 

__attribute__((used)) static int
read_exttime(const char *p, struct rar *rar, const char *endp)
{
  unsigned rmode, flags, rem, j, count;
  int ttime, i;
  struct tm *tm;
  time_t t;
  long nsec;

  if (p + 2 > endp)
    return (-1);
  flags = archive_le16dec(p);
  p += 2;

  for (i = 3; i >= 0; i--)
  {
    t = 0;
    if (i == 3)
      t = rar->mtime;
    rmode = flags >> i * 4;
    if (rmode & 8)
    {
      if (!t)
      {
        if (p + 4 > endp)
          return (-1);
        ttime = archive_le32dec(p);
        t = get_time(ttime);
        p += 4;
      }
      rem = 0;
      count = rmode & 3;
      if (p + count > endp)
        return (-1);
      for (j = 0; j < count; j++)
      {
        rem = (((unsigned)(unsigned char)*p) << 16) | (rem >> 8);
        p++;
      }
      tm = localtime(&t);
      nsec = tm->tm_sec + rem / NS_UNIT;
      if (rmode & 4)
      {
        tm->tm_sec++;
        t = mktime(tm);
      }
      if (i == 3)
      {
        rar->mtime = t;
        rar->mnsec = nsec;
      }
      else if (i == 2)
      {
        rar->ctime = t;
        rar->cnsec = nsec;
      }
      else if (i == 1)
      {
        rar->atime = t;
        rar->ansec = nsec;
      }
      else
      {
        rar->arctime = t;
        rar->arcnsec = nsec;
      }
    }
  }
  return (0);
}
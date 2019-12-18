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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  k ;

/* Variables and functions */
 int BIG_CONSTANT (int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static inline uint64_t MurmurHash64A ( const void * key, int len, uint64_t seed )
{
  const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);
  const int r = 47;

  uint64_t h = seed ^ (len * m);

  const uint64_t * data = (const uint64_t *)key;
  const uint64_t * end = data + (len/8);

  while(data != end)
  {
    uint64_t k;

    if (!((uintptr_t)data & 0x7))
	    k = *data++;
    else {
	    memcpy(&k, data, sizeof(k));
	    data++;
    }

    k *= m;
    k ^= k >> r;
    k *= m;

    h ^= k;
    h *= m;
  }

  const unsigned char * data2 = (const unsigned char*)data;

  switch(len & 7)
  {
  case 7: h ^= (uint64_t)(data2[6]) << 48;
  /* fall through */
  case 6: h ^= (uint64_t)(data2[5]) << 40;
  /* fall through */
  case 5: h ^= (uint64_t)(data2[4]) << 32;
  /* fall through */
  case 4: h ^= (uint64_t)(data2[3]) << 24;
  /* fall through */
  case 3: h ^= (uint64_t)(data2[2]) << 16;
  /* fall through */
  case 2: h ^= (uint64_t)(data2[1]) << 8;
  /* fall through */
  case 1: h ^= (uint64_t)(data2[0]);
          h *= m;
  };

  h ^= h >> r;
  h *= m;
  h ^= h >> r;

  return h;
}
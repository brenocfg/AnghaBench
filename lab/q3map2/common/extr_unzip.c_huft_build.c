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
typedef  int uInt ;
struct inflate_huft_s {int exop; int base; void* bits; } ;
typedef  struct inflate_huft_s inflate_huft ;
typedef  int* C4 ;
typedef  void* Byte ;

/* Variables and functions */
 int BMAX ; 
 int MANY ; 
 int Z_BUF_ERROR ; 
 int Z_DATA_ERROR ; 
 int Z_MEM_ERROR ; 
 scalar_t__ Z_NULL ; 
 int Z_OK ; 

__attribute__((used)) static int huft_build(uInt *b, uInt n, uInt s, const uInt *d, const uInt *e, inflate_huft ** t, uInt *m, inflate_huft *hp, uInt *hn, uInt *v)
//uInt *b;               /* code lengths in bits (all assumed <= BMAX) */
//uInt n;                 /* number of codes (assumed <= 288) */
//uInt s;                 /* number of simple-valued codes (0..s-1) */
//const uInt *d;         /* list of base values for non-simple codes */
//const uInt *e;         /* list of extra bits for non-simple codes */
//inflate_huft ** t;		/* result: starting table */
//uInt *m;               /* maximum lookup bits, returns actual */
//inflate_huft *hp;       /* space for trees */
//uInt *hn;               /* hufts used in space */
//uInt *v;               /* working area: values in order of bit length */
/* Given a list of code lengths and a maximum table size, make a set of
   tables to decode that set of codes.  Return Z_OK on success, Z_BUF_ERROR
   if the given code set is incomplete (the tables are still built in this
   case), Z_DATA_ERROR if the input is invalid (an over-subscribed set of
   lengths), or Z_MEM_ERROR if not enough memory. */
{

  uInt a;                       /* counter for codes of length k */
  uInt c[BMAX+1];               /* bit length count table */
  uInt f;                       /* i repeats in table every f entries */
  int g;                        /* maximum code length */
  int h;                        /* table level */
  register uInt i;              /* counter, current code */
  register uInt j;              /* counter */
  register int k;               /* number of bits in current code */
  int l;                        /* bits per table (returned in m) */
  uInt mask;                    /* (1 << w) - 1, to avoid cc -O bug on HP */
  register uInt *p;            /* pointer into c[], b[], or v[] */
  inflate_huft *q;              /* points to current table */
  struct inflate_huft_s r;      /* table entry for structure assignment */
  inflate_huft *u[BMAX];        /* table stack */
  register int w;               /* bits before this table == (l * h) */
  uInt x[BMAX+1];               /* bit offsets, then code stack */
  uInt *xp;                    /* pointer into x */
  int y;                        /* number of dummy codes added */
  uInt z;                       /* number of entries in current table */


  /* Generate counts for each bit length */
  p = c;
#define C0 *p++ = 0;
#define C2 C0 C0 C0 C0
#define C4 C2 C2 C2 C2
  C4                            /* clear c[]--assume BMAX+1 is 16 */
  p = b;  i = n;
  do {
    c[*p++]++;                  /* assume all entries <= BMAX */
  } while (--i);
  if (c[0] == n)                /* null input--all zero length codes */
  {
    *t = (inflate_huft *)Z_NULL;
    *m = 0;
    return Z_OK;
  }


  /* Find minimum and maximum length, bound *m by those */
  l = *m;
  for (j = 1; j <= BMAX; j++)
    if (c[j])
      break;
  k = j;                        /* minimum code length */
  if ((uInt)l < j)
    l = j;
  for (i = BMAX; i; i--)
    if (c[i])
      break;
  g = i;                        /* maximum code length */
  if ((uInt)l > i)
    l = i;
  *m = l;


  /* Adjust last length count to fill out codes, if needed */
  for (y = 1 << j; j < i; j++, y <<= 1)
    if ((y -= c[j]) < 0)
      return Z_DATA_ERROR;
  if ((y -= c[i]) < 0)
    return Z_DATA_ERROR;
  c[i] += y;


  /* Generate starting offsets into the value table for each length */
  x[1] = j = 0;
  p = c + 1;  xp = x + 2;
  while (--i) {                 /* note that i == g from above */
    *xp++ = (j += *p++);
  }


  /* Make a table of values in order of bit lengths */
  p = b;  i = 0;
  do {
    if ((j = *p++) != 0)
      v[x[j]++] = i;
  } while (++i < n);
  n = x[g];                     /* set n to length of v */


  /* Generate the Huffman codes and for each, make the table entries */
  x[0] = i = 0;                 /* first Huffman code is zero */
  p = v;                        /* grab values in bit order */
  h = -1;                       /* no tables yet--level -1 */
  w = -l;                       /* bits decoded == (l * h) */
  u[0] = (inflate_huft *)Z_NULL;        /* just to keep compilers happy */
  q = (inflate_huft *)Z_NULL;   /* ditto */
  z = 0;                        /* ditto */

  /* go through the bit lengths (k already is bits in shortest code) */
  for (; k <= g; k++)
  {
    a = c[k];
    while (a--)
    {
      /* here i is the Huffman code of length k bits for value *p */
      /* make tables up to required level */
      while (k > w + l)
      {
        h++;
        w += l;                 /* previous table always l bits */

        /* compute minimum size table less than or equal to l bits */
        z = g - w;
        z = z > (uInt)l ? l : z;        /* table size upper limit */
        if ((f = 1 << (j = k - w)) > a + 1)     /* try a k-w bit table */
        {                       /* too few codes for k-w bit table */
          f -= a + 1;           /* deduct codes from patterns left */
          xp = c + k;
          if (j < z)
            while (++j < z)     /* try smaller tables up to z bits */
            {
              if ((f <<= 1) <= *++xp)
                break;          /* enough codes to use up j bits */
              f -= *xp;         /* else deduct codes from patterns */
            }
        }
        z = 1 << j;             /* table entries for j-bit table */

        /* allocate new table */
        if (*hn + z > MANY)     /* (note: doesn't matter for fixed) */
          return Z_MEM_ERROR;   /* not enough memory */
        u[h] = q = hp + *hn;
        *hn += z;

        /* connect to last table, if there is one */
        if (h)
        {
          x[h] = i;             /* save pattern for backing up */
          r.bits = (Byte)l;     /* bits to dump before this table */
          r.exop = (Byte)j;     /* bits in this table */
          j = i >> (w - l);
          r.base = (uInt)(q - u[h-1] - j);   /* offset to this table */
          u[h-1][j] = r;        /* connect to last table */
        }
        else
          *t = q;               /* first table is returned result */
      }

      /* set up table entry in r */
      r.bits = (Byte)(k - w);
      if (p >= v + n)
        r.exop = 128 + 64;      /* out of values--invalid code */
      else if (*p < s)
      {
        r.exop = (Byte)(*p < 256 ? 0 : 32 + 64);     /* 256 is end-of-block */
        r.base = *p++;          /* simple code is just the value */
      }
      else
      {
        r.exop = (Byte)(e[*p - s] + 16 + 64);/* non-simple--look up in lists */
        r.base = d[*p++ - s];
      }

      /* fill code-like entries with r */
      f = 1 << (k - w);
      for (j = i >> w; j < z; j += f)
        q[j] = r;

      /* backwards increment the k-bit code i */
      for (j = 1 << (k - 1); i & j; j >>= 1)
        i ^= j;
      i ^= j;

      /* backup over finished tables */
      mask = (1 << w) - 1;      /* needed on HP, cc -O bug */
      while ((i & mask) != x[h])
      {
        h--;                    /* don't need to update q */
        w -= l;
        mask = (1 << w) - 1;
      }
    }
  }


  /* Return Z_BUF_ERROR if we were given an incomplete table */
  return y != 0 && g != 1 ? Z_BUF_ERROR : Z_OK;
}
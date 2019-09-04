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
typedef  int /*<<< orphan*/  reg_errcode_t ;
typedef  int /*<<< orphan*/  bitset_t ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ECOLLATE ; 
 int /*<<< orphan*/  REG_NOERROR ; 
 int /*<<< orphan*/  bitset_set (int /*<<< orphan*/ ,unsigned char const) ; 
 int strlen (char const*) ; 

__attribute__((used)) static reg_errcode_t
#ifdef RE_ENABLE_I18N
build_equiv_class (bitset_t sbcset, re_charset_t *mbcset,
		   int *equiv_class_alloc, const unsigned char *name)
#else /* not RE_ENABLE_I18N */
build_equiv_class (bitset_t sbcset, const unsigned char *name)
#endif /* not RE_ENABLE_I18N */
{
#ifdef _LIBC
  uint32_t nrules = _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_NRULES);
  if (nrules != 0)
    {
      const int32_t *table, *indirect;
      const unsigned char *weights, *extra, *cp;
      unsigned char char_buf[2];
      int32_t idx1, idx2;
      unsigned int ch;
      size_t len;
      /* This #include defines a local function!  */
# include <locale/weight.h>
      /* Calculate the index for equivalence class.  */
      cp = name;
      table = (const int32_t *) _NL_CURRENT (LC_COLLATE, _NL_COLLATE_TABLEMB);
      weights = (const unsigned char *) _NL_CURRENT (LC_COLLATE,
					       _NL_COLLATE_WEIGHTMB);
      extra = (const unsigned char *) _NL_CURRENT (LC_COLLATE,
						   _NL_COLLATE_EXTRAMB);
      indirect = (const int32_t *) _NL_CURRENT (LC_COLLATE,
						_NL_COLLATE_INDIRECTMB);
      idx1 = findidx (&cp);
      if (BE (idx1 == 0 || cp < name + strlen ((const char *) name), 0))
	/* This isn't a valid character.  */
	return REG_ECOLLATE;

      /* Build single byte matcing table for this equivalence class.  */
      char_buf[1] = (unsigned char) '\0';
      len = weights[idx1 & 0xffffff];
      for (ch = 0; ch < SBC_MAX; ++ch)
	{
	  char_buf[0] = ch;
	  cp = char_buf;
	  idx2 = findidx (&cp);
/*
	  idx2 = table[ch];
*/
	  if (idx2 == 0)
	    /* This isn't a valid character.  */
	    continue;
	  /* Compare only if the length matches and the collation rule
	     index is the same.  */
	  if (len == weights[idx2 & 0xffffff] && (idx1 >> 24) == (idx2 >> 24))
	    {
	      int cnt = 0;

	      while (cnt <= len &&
		     weights[(idx1 & 0xffffff) + 1 + cnt]
		     == weights[(idx2 & 0xffffff) + 1 + cnt])
		++cnt;

	      if (cnt > len)
		bitset_set (sbcset, ch);
	    }
	}
      /* Check whether the array has enough space.  */
      if (BE (*equiv_class_alloc == mbcset->nequiv_classes, 0))
	{
	  /* Not enough, realloc it.  */
	  /* +1 in case of mbcset->nequiv_classes is 0.  */
	  int new_equiv_class_alloc = 2 * mbcset->nequiv_classes + 1;
	  /* Use realloc since the array is NULL if *alloc == 0.  */
	  int32_t *new_equiv_classes = re_realloc (mbcset->equiv_classes,
						   int32_t,
						   new_equiv_class_alloc);
	  if (BE (new_equiv_classes == NULL, 0))
	    return REG_ESPACE;
	  mbcset->equiv_classes = new_equiv_classes;
	  *equiv_class_alloc = new_equiv_class_alloc;
	}
      mbcset->equiv_classes[mbcset->nequiv_classes++] = idx1;
    }
  else
#endif /* _LIBC */
    {
      if (BE (strlen ((const char *) name) != 1, 0))
	return REG_ECOLLATE;
      bitset_set (sbcset, *name);
    }
  return REG_NOERROR;
}
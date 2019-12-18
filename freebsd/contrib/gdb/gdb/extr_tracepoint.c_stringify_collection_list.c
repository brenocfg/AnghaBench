#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct collection_list {int next_memrange; int next_aexpr_elt; scalar_t__* regs_mask; TYPE_2__** aexpr_list; TYPE_1__* list; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {int type; scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int MAX_AGENT_EXPR_LEN ; 
 int /*<<< orphan*/  QUIT ; 
 scalar_t__ info_verbose ; 
 char* mem2hex (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 char* savestring (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  sprintf_vma (char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static char **
stringify_collection_list (struct collection_list *list, char *string)
{
  char temp_buf[2048];
  char tmp2[40];
  int count;
  int ndx = 0;
  char *(*str_list)[];
  char *end;
  long i;

  count = 1 + list->next_memrange + list->next_aexpr_elt + 1;
  str_list = (char *(*)[]) xmalloc (count * sizeof (char *));

  for (i = sizeof (list->regs_mask) - 1; i > 0; i--)
    if (list->regs_mask[i] != 0)	/* skip leading zeroes in regs_mask */
      break;
  if (list->regs_mask[i] != 0)	/* prepare to send regs_mask to the stub */
    {
      if (info_verbose)
	printf_filtered ("\nCollecting registers (mask): 0x");
      end = temp_buf;
      *end++ = 'R';
      for (; i >= 0; i--)
	{
	  QUIT;			/* allow user to bail out with ^C */
	  if (info_verbose)
	    printf_filtered ("%02X", list->regs_mask[i]);
	  sprintf (end, "%02X", list->regs_mask[i]);
	  end += 2;
	}
      (*str_list)[ndx] = savestring (temp_buf, end - temp_buf);
      ndx++;
    }
  if (info_verbose)
    printf_filtered ("\n");
  if (list->next_memrange > 0 && info_verbose)
    printf_filtered ("Collecting memranges: \n");
  for (i = 0, count = 0, end = temp_buf; i < list->next_memrange; i++)
    {
      QUIT;			/* allow user to bail out with ^C */
      sprintf_vma (tmp2, list->list[i].start);
      if (info_verbose)
	{
	  printf_filtered ("(%d, %s, %ld)\n", 
			   list->list[i].type, 
			   tmp2, 
			   (long) (list->list[i].end - list->list[i].start));
	}
      if (count + 27 > MAX_AGENT_EXPR_LEN)
	{
	  (*str_list)[ndx] = savestring (temp_buf, count);
	  ndx++;
	  count = 0;
	  end = temp_buf;
	}

      sprintf (end, "M%X,%s,%lX", 
	       list->list[i].type,
	       tmp2,
	       (long) (list->list[i].end - list->list[i].start));

      count += strlen (end);
      end += count;
    }

  for (i = 0; i < list->next_aexpr_elt; i++)
    {
      QUIT;			/* allow user to bail out with ^C */
      if ((count + 10 + 2 * list->aexpr_list[i]->len) > MAX_AGENT_EXPR_LEN)
	{
	  (*str_list)[ndx] = savestring (temp_buf, count);
	  ndx++;
	  count = 0;
	  end = temp_buf;
	}
      sprintf (end, "X%08X,", list->aexpr_list[i]->len);
      end += 10;		/* 'X' + 8 hex digits + ',' */
      count += 10;

      end = mem2hex (list->aexpr_list[i]->buf, end, list->aexpr_list[i]->len);
      count += 2 * list->aexpr_list[i]->len;
    }

  if (count != 0)
    {
      (*str_list)[ndx] = savestring (temp_buf, count);
      ndx++;
      count = 0;
      end = temp_buf;
    }
  (*str_list)[ndx] = NULL;

  if (ndx == 0)
    return NULL;
  else
    return *str_list;
}
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
struct TYPE_3__ {char* Comment; struct TYPE_3__* Next; } ;

/* Variables and functions */
 TYPE_1__* AslGbl_CommentListHead ; 
 TYPE_1__* AslGbl_CommentListTail ; 
 void* CvCommentNodeCalloc () ; 

void
CvAddToCommentList (
    char                    *ToAdd)
{

   if (AslGbl_CommentListHead)
   {
       AslGbl_CommentListTail->Next = CvCommentNodeCalloc ();
       AslGbl_CommentListTail = AslGbl_CommentListTail->Next;
   }
   else
   {
       AslGbl_CommentListHead = CvCommentNodeCalloc ();
       AslGbl_CommentListTail = AslGbl_CommentListHead;
   }

   AslGbl_CommentListTail->Comment = ToAdd;
}
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
typedef  int /*<<< orphan*/  svn_rangelist_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_rangelist_remove (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_rangelist_diff(svn_rangelist_t **deleted, svn_rangelist_t **added,
                   const svn_rangelist_t *from, const svn_rangelist_t *to,
                   svn_boolean_t consider_inheritance,
                   apr_pool_t *pool)
{
  /* The following diagrams illustrate some common range delta scenarios:

     (from)           deleted
     r0 <===========(=========)============[=========]===========> rHEAD
     [to]                                    added

     (from)           deleted                deleted
     r0 <===========(=========[============]=========)===========> rHEAD
     [to]

     (from)           deleted
     r0 <===========(=========[============)=========]===========> rHEAD
     [to]                                    added

     (from)                                  deleted
     r0 <===========[=========(============]=========)===========> rHEAD
     [to]             added

     (from)
     r0 <===========[=========(============)=========]===========> rHEAD
     [to]             added                  added

     (from)  d                                  d             d
     r0 <===(=[=)=]=[==]=[=(=)=]=[=]=[=(===|===(=)==|=|==[=(=]=)=> rHEAD
     [to]        a   a    a   a   a   a                   a
  */

  /* The items that are present in from, but not in to, must have been
     deleted. */
  SVN_ERR(svn_rangelist_remove(deleted, to, from, consider_inheritance,
                               pool));
  /* The items that are present in to, but not in from, must have been
     added.  */
  return svn_rangelist_remove(added, from, to, consider_inheritance, pool);
}